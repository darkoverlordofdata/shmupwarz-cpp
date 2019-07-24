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
#include "../Core/EntitySystem.hpp"

namespace artemis::systems 
{
    using namespace std;
    using namespace artemis;

    class EntitySystem;
    class Aspect;

    /**
     * This system has an empty aspect so it processes no entities, but it still gets invoked.
     * You can use this system if you need to execute some game logic and not have to concern
     * yourself about aspects or entities.
     *
     * @author Arni Arent
     *
     */
    class VoidEntitySystem : public artemis::EntitySystem {

        public:
        VoidEntitySystem() : EntitySystem(artemis::Aspect::GetEmpty())
        {}


        protected :
        void ProcessEntities(vector<IEntity*>* entities) {
            ProcessSystem();
        }

        virtual void ProcessSystem() = 0;


        bool CheckProcessing() {
            return true;
        }

    };
}