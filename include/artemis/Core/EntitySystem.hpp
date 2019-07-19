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
#include "World.hpp"
#include "EntityObserver.hpp"

namespace artemis 
{
    class World;

    class EntitySystem 
    {
        private:
        World* mWorld;
        bool mPassive;

        public:
        void Check(Entity* e)
        {

        }

        void Process() {
            // if (CheckProcessing()) {
            //     Begin();
            //     ProcessEntities(actives);
            //     End();
            // }
        }


        void Added(Entity* e) {
            Check(e);
        }
        
        void Changed(Entity* e) {
            Check(e);
        }
        
        void Deleted(Entity* e) {
            // if(e.SystemBits[systemIndex]) {
            //     RemoveFromSystem(e);
            // }
        }
        
        void Disabled(Entity* e) {
            // if(e.SystemBits[systemIndex]) {
            //     RemoveFromSystem(e);
            // }
        }

        void Enabled(Entity* e) {
            Check(e);
        }

        void SetWorld(World* world) {
            mWorld = world;
        }
        
        bool IsPassive() {
            return mPassive;
        }
    
        void SetPassive(bool passive) {
            mPassive = passive;
        }


    };
}