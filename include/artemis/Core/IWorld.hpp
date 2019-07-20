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
#include "IManager.hpp"
#include "IEntityObserver.hpp"
#include "IEntitySystem.hpp"
#include "IEntityManager.hpp"
#include "IComponentManager.hpp"
#include "IComponentMapper.hpp"
#include "IEntityObserver.hpp"
#include "IType.hpp"
#include "IFactory.hpp"

namespace artemis 
{

    typedef void (*Performer) (IEntityObserver* observer, IEntity* e);

    using namespace std;
    
    class IWorld {

        public:
        virtual void Initialize(IFactory* factory) = 0;
        virtual IEntityManager * GetEntityManager() = 0;
        virtual IComponentManager * GetComponentManager() = 0;
        virtual IManager* SetManager(IManager * manager) = 0; 
        virtual IManager* GetManager(type_info& managerType) = 0;
        virtual void DeleteManager(IManager* manager) = 0;
        virtual float GetDelta() = 0;
        virtual void SetDelta(float delta) = 0;
        virtual void AddEntity(IEntity * e) = 0;
        virtual void ChangedEntity(IEntity * e) = 0;
        virtual void DeleteEntity(IEntity * e) = 0;
        virtual void Enable(IEntity * e) = 0;
        virtual void Disable(IEntity * e) = 0;
        virtual IEntity* CreateEntity(string name="") = 0;
        virtual IEntity* GetEntity(int entityId) = 0;
        virtual vector<IEntitySystem*>* GetSystems() = 0;
        virtual IEntitySystem* SetSystem(IEntitySystem* system, bool passive=false) = 0;
        virtual void DeleteSystem(IEntitySystem* system) = 0;
        virtual IEntitySystem* GetSystem(type_info& type) = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;
        virtual IComponentMapper* GetMapper(type_info& type) = 0;
    };
}