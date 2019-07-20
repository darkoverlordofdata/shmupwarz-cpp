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
#include "Manager.hpp"
#include "IEntity.hpp"

namespace artemis 
{
    using namespace std;
    class Manager;
    class IEntity;

    class EntityManager : public Manager 
    {
        private:
        vector<IEntity*> mEntities;
		bitset<BITSIZE> mDisabled;
		int mActive;
		int mAdded;
		int mCreated;
		int mDeleted;
        int mId;

        public:
		EntityManager() {
			mActive = 0;
            mAdded = 0;
            mCreated = 0;
            mDeleted = 0;
		}

		IEntity* CreateEntityInstance(string name = "") 
        {
			auto e = mFactory->CreateEntity(mWorld, mId++, name);
			mCreated++;
			return e;
		}

		void Added(IEntity* e) {
			mActive++;
			mAdded++;
			mEntities[e->Id()] = e;
		}
		
		
		void Enabled(IEntity* e) {
			mDisabled.reset(e->Id());
		}
		
		
		void Disabled(IEntity* e) {
			mDisabled.set(e->Id(), true);
		}
		
		
		void Deleted(IEntity* e) {
			mEntities[e->Id()] = nullptr;
			
			mDisabled.reset(e->Id());
			
			// identifierPool.CheckIn(e.Id);
			
			mActive--;
			mDeleted++;
		}
	

		/**
		* Get a entity with this id.
		* 
		* @param entityId
		* @return the entity
		*/
		IEntity* GetEntity(int entityId) 
        {
			return mEntities[entityId];
		}



    };
}