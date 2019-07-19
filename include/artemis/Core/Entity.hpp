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
#include <string>
#include <bitset>
#include "World.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"

namespace artemis 
{

    class EntityManager;
    class World;
    
    class Entity {
        private:
        std::string mName;
        int mId;
        std::bitset<BITSIZE> mComponentBits;
        std::bitset<BITSIZE> mSystemBits;
        World * mWorld;
        EntityManager mEntityManager;
        ComponentManager mComponentManager;

        public:
        int Id() { return mId; }
        std::string Name() { return mName; }
        std::bitset<BITSIZE> ComponentBits() { return mComponentBits; }
        std::bitset<BITSIZE> SystemBits() { return mSystemBits; }

        Entity(World* world, int id, std::string name="") {
            mWorld = world;
            mId = id;
            mName = name;
        }



    };
}