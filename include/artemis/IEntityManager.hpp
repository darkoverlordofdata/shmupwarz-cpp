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
#include <string>
#include "IManager.hpp"
#include "IEntity.hpp"
#include "IFactory.hpp"

namespace artemis 
{
    using namespace std;
    class IManager;
    // class IEntity;

    class IEntityManager : public IManager 
    {
        public:
		~IEntityManager(){}
        // virtual void Initialize(IFactory* factory)  = 0;
		virtual IEntity* CreateEntityInstance(string name = "") = 0;
		// virtual void Added(IEntity* e) = 0;
		// virtual void Deleted(IEntity* e) = 0;
		// virtual void Disabled(IEntity* e) = 0;
		// virtual void Enabled(IEntity* e) = 0;
		virtual bool IsActive(int entityId) = 0;
		virtual bool IsEnabled(int entityId) = 0;
		virtual IEntity* GetEntity(int entityId) = 0;
		virtual int GetActiveEntityCount() = 0;
		virtual int GetTotalCreated() = 0;
		virtual int GetTotalAdded() = 0;
		virtual int GetTotalDeleted() = 0;

    };
}