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
#include "../IManager.hpp"
#include "../IEntity.hpp"

namespace artemis 
{
    using namespace std;
    class Manager;
    class IEntity;

    class EntityManager : public IEntityManager
    {

		/*
		* Used internally by EntityManager to generate distinct ids for entities and reuse them.
		*/
		class IdentifierPool {
			private:
			vector<int>* ids;
			int nextAvailableId=0;

			public:
			IdentifierPool() {
				ids = new vector<int>();
			}
			
			int CheckOut() {
				if (ids->size() > 0) {
					auto result = ids->back();
					ids->pop_back();
					return result;
				}
				return nextAvailableId++;
			}
			
			void CheckIn(int id) {
				ids->push_back(id);
			}
		};

        private:
        vector<IEntity*> mEntities;
		bitset<BITSIZE> mDisabled;
		int mActive;
		int mAdded;
		int mCreated;
		int mDeleted;
        int mId;
		IdentifierPool identifierPool;


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

		void Added(IEntity* e)
		{
			mActive++;
			mAdded++;
			mEntities[e->Id()] = e;
		}		
		
		void Enabled(IEntity* e)
		{
			mDisabled.reset(e->Id());
		}		
		
		void Disabled(IEntity* e)
		{
			mDisabled.set(e->Id(), true);
		}
				
		void Deleted(IEntity* e)
		{
			mEntities[e->Id()] = nullptr;
			mDisabled.reset(e->Id());
			identifierPool.CheckIn(e->Id());
			mActive--;
			mDeleted++;
		}
	
		/**
		* Check if this entity is active.
		* Active means the entity is being actively processed.
		* 
		* @param entityId
		* @return true if active, false if not.
		*/
		bool IsActive(int entityId)
		{

			return mEntities[entityId] != nullptr;
		}
		
		/**
		* Check if the specified entityId is enabled.
		* 
		* @param entityId
		* @return true if the entity is enabled, false if it is disabled.
		*/
		bool IsEnabled(int entityId)
		{
			return !mDisabled.test(entityId);
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
		
		/**
		* Get how many entities are active in this world.
		* @return how many entities are currently active.
		*/
		int GetActiveEntityCount()
		{
			return mActive;
		}
		
		/**
		* Get how many entities have been created in the world since start.
		* Note: A created entity may not have been added to the world, thus
		* created count is always equal or larger than added count.
		* @return how many entities have been created since start.
		*/
		int GetTotalCreated()
		{
			return mCreated;
		}
		
		/**
		* Get how many entities have been added to the world since start.
		* @return how many entities have been added.
		*/
		int GetTotalAdded()
		{
			return mAdded;
		}
		
		/**
		* Get how many entities have been deleted from the world since start.
		* @return how many entities have been deleted since start.
		*/
		int GetTotalDeleted()
		{
			return mDeleted;
		}

    };
}