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
#include "Manager.hpp"
#include "Entity.hpp"

namespace artemis 
{
    using namespace std;
    class Manager;
    class Entity;

    class EntityManager : public Manager 
    {
        private:
        vector<Entity*> mEntities;
		int mActive;
		int mAdded;
		int mCreated;
		int mDeleted;
        int mId;
        public:

        public:

        void Initialize(IFactory* factory) 
        {
            mFactory = factory;
        }


		/**
		* Get a entity with this id.
		* 
		* @param entityId
		* @return the entity
		*/
		Entity* GetEntity(int entityId) 
        {
			return mEntities[entityId];
		}

		Entity* CreateEntityInstance(string name = "") 
        {
			auto e = mFactory->CreateEntity(mWorld, mId++, name);
			mCreated++;
			return e;
		}


    };
}