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
#pragma once
#include "../IAspect.hpp"
#include "../Core/EntitySystem.hpp"
#include "../Core/World.hpp"


namespace artemis::systems 
{
    using namespace std;
    using namespace artemis;

    class EntitySystem;
    class IAspect;

    /**
     * A system that processes entities at a interval in milliseconds.
     * A typical usage would be a collision system or physics system.
     *
     * @author Arni Arent
     *
     */
    class IntervalEntitySystem : public artemis::EntitySystem {
        private:
        float mAcc = 0;
        float mInterval = 0;

        public:
        IntervalEntitySystem() {}
        IntervalEntitySystem(artemis::IAspect* aspect, float interval) 
            : EntitySystem(aspect) { 
            mInterval = interval;
        }


        protected:
        bool CheckProcessing() {

            if ((mAcc += World::GetDelta()) >= mInterval) {
                mAcc -= mInterval;
                return true;
            }
            return false;
        }


    };
} 