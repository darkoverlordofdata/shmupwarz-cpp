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
#include <vector>
#include <algorithm>
#include "../IAspect.hpp"
#include "../IWorld.hpp"
#include "../IEntityObserver.hpp"
#include "../IEntitySystem.hpp"
#include "../Blackboard/Blackboard.hpp"

namespace artemis 
{
    using namespace std;

    class IWorld;
    class IAspect;

    /**
     * The most raw entity system. It should not typically be used, but you can create your own
     * entity system handling by extending  It is recommended that you use the other provided
     * entity system implementations.
     * 
     * @author Arni Arent
     *
     */
    class EntitySystem : IEntitySystem
    {
        protected:

        int mSystemIndex;
        IWorld* mWorld;
        vector<IEntity*> mActives;
        IAspect* mAspect;
    
        bitset<BITSIZE> mAllSet;
        bitset<BITSIZE> mExclusionSet;
        bitset<BITSIZE> mOneSet;
        bool mPassive;
        bool mDummy;

        public:
        static inline BlackBoard BlackBoard;

        protected:
        /**
         * Used to generate a unique bit for each system.
         * Only used internally by EntitySystem.
         */
        class SystemIndexManager
        {
            private:
            inline static int INDEX = 0;
            inline static unordered_map<type_index, int> indices;

            public:
            static int GetIndexFor(type_index es) 
            {

                auto index = 0;
                
                if (indices.find(es) != indices.end()) 
                {
                    index = indices[es];
                } 
                else 
                {
                    index = INDEX++;
                    indices[es] = index;
                }
                return index;
            }
        };

        public:
        /**
         * Creates an entity system that uses the specified aspect as a matcher against entities.
         * @param aspect to match against entities
         */
        EntitySystem() {}
        EntitySystem(IAspect* aspect) : mAspect(aspect)
        {
            mSystemIndex = SystemIndexManager::GetIndexFor(TypeOf(this));
            mAllSet = mAspect->GetAllSet();
            mExclusionSet = mAspect->GetExclusionSet();
            mOneSet = mAspect->GetOneSet();
            mDummy = mAllSet.none() && mOneSet.none(); // This system can't possibly be interested in any entity, so it must be "dummy"


        }
        ~EntitySystem(){}

        /**
         * Called before processing of entities begins. 
         */
        void Begin() {}
    
        void Process() {
            if (CheckProcessing()) {
                Begin();
                ProcessEntities(mActives);
                End();
            }
        }
        
        /**
         * Called after the processing of entities ends.
         */
        void End() {}
        
        /**
         * Any implementing entity system must implement this method and the logic
         * to process the given entities of the system.
         * 
         * @param entities the entities this system contains.
         */
        virtual void ProcessEntities(vector<IEntity*> entities) = 0;
        
        /**
         * 
         * @return true if the system should be processed, false if not.
         */
        bool CheckProcessing() {
            return true;
        }
    
        /**
         * Override to implement code that gets executed when systems are initialized.
         */
        void Initialize() {}
    
        /**
         * Called if the system has received a entity it is interested in, e.g. created or a component was added to it.
         * @param e the entity that was added to this system.
         */
        void Inserted(IEntity* e) {}
    
        /**
         * Called if a entity was removed from this system, e.g. deleted or had one of it's components removed.
         * @param e the entity that was removed from this system.
         */
        void Removed(IEntity* e) {}
    
        /**
         * Will Check if the entity is of interest to this system.
         * @param e entity to Check
         */
        void Check(IEntity* e) {
            if (mDummy) {
                return;
            }
            auto contains = e->SystemBits[mSystemIndex];
            auto interested = true; // possibly interested, let's try to prove it wrong.
            
            auto componentBits = e->ComponentBits;
    
            // Check if the entity possesses ALL of the components defined in the aspect.
            if (!mAllSet.none()) {
                for (auto i = 0; i<mAllSet.size(); i++) {
                // for (auto i = mAllSetNextSetBit(0); i >= 0; i = mAllSetNextSetBit(i+1)) {
                    if (!componentBits.test(i)) {
                        interested = false;
                        break;
                    }
                }
            }

            // Check if the entity possesses ANY of the exclusion components, if it does then the system is not interested.
            if (!mExclusionSet.none() && interested) {
                interested = (~( mExclusionSet &= componentBits )).any();
                // interested = !mExclusionSet.Intersects(componentBits);
            }
            
            // Check if the entity possesses ANY of the components in the mOneSet. If so, the system is interested.
            if(!mOneSet.none()) {
                interested = ( mOneSet &= componentBits ).any();
                // interested = mOneSet.Intersects(componentBits);
            }

            if (interested && !contains) 
            {
                InsertToSystem(e);
            } 
            else if (!interested && contains) 
            {
                RemoveFromSystem(e);
            }
        }
    
        void RemoveFromSystem(IEntity* e) {
            mActives.erase(find(mActives.begin(), mActives.end(), e));
            e->SystemBits.reset(mSystemIndex);
            Removed(e);
        }
    
        void InsertToSystem(IEntity* e) {
            mActives.push_back(e);
            e->SystemBits.set(mSystemIndex, true);
            Inserted(e);
        }
        


        void Added(IEntity* e) {
            Check(e);
        }
        
        void Changed(IEntity* e) {
            Check(e);
        }
        
        void Deleted(IEntity* e) {
            if(e->SystemBits.test(mSystemIndex)) {
                RemoveFromSystem(e);
            }
        }
        
        void Disabled(IEntity* e) {
            if(e->SystemBits.test(mSystemIndex)) {
                RemoveFromSystem(e);
            }
        }

        void Enabled(IEntity* e) {
            Check(e);
        }

        void SetWorld(IWorld* world) {
            mWorld = world;
        }
        
        bool IsPassive() {
            return mPassive;
        }
    
        void SetPassive(bool passive) {
            mPassive = passive;
        }

        vector<IEntity*>* GetActive() {
            return &mActives;
        }

    };

}