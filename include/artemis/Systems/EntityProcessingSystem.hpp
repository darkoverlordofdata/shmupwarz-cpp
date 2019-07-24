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
#include "../Core/IEntity.hpp"
#include "../Core/Aspect.hpp"
#include "../Core/EntitySystem.hpp"

namespace artemis::systems 
{
    using namespace std;
    using namespace artemis;

    class EntitySystem;
    class Aspect;

    /**
     * A typical entity system. Use this when you need to process entities possessing the
     * provided component types.
     *
     * @author Arni Arent
     *
     */
    class EntityProcessingSystem : public artemis::EntitySystem {

        public:
        EntityProcessingSystem(artemis::IAspect* aspect) 
        : artemis::EntitySystem(aspect) { }

        /**
         * Process a entity this system is interested in.
        * @param e the entity to process.
        */
        protected:
        virtual void ProcessEach(IEntity* e);


        void ProcessEntities(vector<IEntity*>* entities) 
        {   
            for (auto entity : *entities)
                ProcessEach(entity);
        }


        bool CheckProcessing() 
        {
            return true;
        }

    };
}