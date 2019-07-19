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
#include "IFactory.hpp"

/**
 * IFactory implementation
 * 
 * This seperates object creation from the rest of the framework so that
 * we can avoid cyclic refrences that require a completed type definition.
 */
namespace artemis
{
    using namespace std;
    
    class World;
    class Entity;

    class Factory : public IFactory
    {
        public:
        Entity* CreateEntity(World* world, int id, string name) override
        {
            return new Entity(world, id, name);
        }

    };

}