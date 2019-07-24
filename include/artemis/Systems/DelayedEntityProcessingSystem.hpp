/* ******************************************************************************
 * Copyright 2019 darkoverlordofdata.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
#pragma once;
#include "../IEntity.hpp"
#include "../Core/Aspect.hpp"
#include "../Core/World.hpp"
#include "../Core/EntitySystem.hpp"

namespace artemis::systems 
{
    using namespace std;
    using namespace artemis;

    class EntitySystem;
    class Aspect;

    /**
     * The purpose of this class is to allow systems to execute at varying intervals.
     *
     * An example system would be an ExpirationSystem, that deletes entities after a certain
     * lifetime. Instead of running a system that decrements a timeLeft value for each
     * entity, you can simply use this system to execute in a future at a time of the shortest
     * lived entity, and then reset the system to run at a time in a future at a time of the
     * shortest lived entity, etc.
     *
     * Another example system would be an AnimationSystem. You know when you have to animate
     * a certain entity, e.g. in 300 milliseconds. So you can set the system to run in 300 ms.
     * to perform the animation.
     *
     * This will save CPU cycles in some scenarios.
     *
     * Implementation notes:
     * In order to start the system you need to override the inserted(Entity e) method,
     * look up the delay time from that entity and offer it to the system by using the
     * offerDelay(float delay) method.
     * Also, when processing the entities you must also call offerDelay(float delay)
     * for all valid entities.
     *
     * @author Arni Arent
     *
     */
    class DelayedEntityProcessingSystem : public artemis::EntitySystem {

        private:
        /** The time until an entity should be processed. */
        float mDelay;
        /**	If the system is running and counting down delays. */
        bool mRunning;
        /** The countdown, accumulates world deltas. */
        float mAcc;

        public:
        DelayedEntityProcessingSystem(artemis::IAspect* aspect) 
        : artemis::EntitySystem(aspect) { }

        protected:
        void ProcessEntities(vector<Entity*>* entities) {
            for (auto entity : *entities)
            {
                ProcessDelta(entity, mAcc);
                auto remaining = GetRemainingDelay(entity);
                if (remaining <= 0) {
                    ProcessExpired(entity);
                } else {
                    OfferDelay(remaining);
                }
            }
            Stop();
        }

        public:
        void Inserted(IEntity* e) {
            auto delay = GetRemainingDelay(e);
            if (delay > 0) {
                OfferDelay(delay);
            }
        }

        /**
         * Return the delay until this entity should be processed.
        *
        * @param e entity
        * @return delay
        */
        protected:
        virtual float GetRemainingDelay(IEntity* e);

        bool CheckProcessing() {
            if (mRunning) {
                mAcc += World::GetDelta();
                if (mAcc >= mDelay) {
                    return true;
                }
            }
            return false;
        }


        /**
         * Process a entity this system is interested in. Substract the accumulatedDelta
        * from the entities defined delay.
        *
        * @param e the entity to process.
        * @param accumulatedDelta the delta time since this system was last executed.
        */
        virtual void ProcessDelta(IEntity* e, float accumulatedDelta);

        virtual void ProcessExpired(IEntity* e);


        /**
         * Start processing of entities after a certain amount of delta time.
        *
        * Cancels current delayed run and starts a new one.
        *
        * @param delta time delay until processing starts.
        */
        public:
        void Restart(float delay) {
            mDelay = delay;
            mAcc = 0;
            mRunning = true;
        }

        /**
         * Restarts the system only if the delay offered is shorter than the
        * time that the system is currently scheduled to execute at.
        * If the system is already stopped (not running) then the offered
        *
        * delay will be used to restart the system with no matter its value.
        *
        * If the system is already counting down, and the offered delay is
        * larger than the time remaining, the system will ignore it. If the
        * offered delay is shorter than the time remaining, the system will
        * restart itself to run at the offered delay.
        *
        * @param delay
        */
        void OfferDelay(float delay) {
            if(!mRunning || delay < GetRemainingTimeUntilProcessing()) {
                Restart(delay);
            }
        }


        /**
         * Get the initial delay that the system was ordered to process entities after.
        *
        * @return the originally set delay.
        */
        float GetInitialTimeDelay() {
            return mDelay;
        }

        /**
         * Get the time until the system is scheduled to run at.
        * Returns zero (0) if the system is not running.
        * Use isRunning() before checking this value.
        *
        * @return time when system will run at.
        */
        float GetRemainingTimeUntilProcessing() {
            if(mRunning) {
                return mDelay-mAcc;
            }
            return 0;
        }

        /**
         * Check if the system is counting down towards processing.
        *
        * @return true if it's counting down, false if it's not running.
        */
        bool IsRunning() {
            return mRunning;
        }

        /**
         * Stops the system from running, aborts current countdown.
        * Call offerDelay or restart to run it again.
        */
        void Stop() {
            mRunning = false;
            mAcc = 0;
        }

    };
}