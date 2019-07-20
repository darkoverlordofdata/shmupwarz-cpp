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
#include "IEntity.hpp"
#include "IComponent.hpp"
#include "IComponentType.hpp"
#include "IManager.hpp"

namespace artemis 
{
    using namespace std;
    class IFactory;
    class IEntity;
    class IComponent;
    class IComponentType;
    class IManager;
    class IComponentManager : public IManager 
    {
        public:
        virtual void Initialize(IFactory* factory) = 0;
        virtual void AddComponent(IEntity e, IComponentType type, IComponent component) = 0;
        virtual void RemoveComponent(IEntity e, IComponentType type) = 0;
        virtual vector<IComponent> GetComponentsByType(IComponentType type) = 0;
        virtual IComponent* GetComponent(IEntity e, IComponentType type) = 0;
        virtual vector<IComponent> GetComponentsFor(IEntity e,  vector<IComponent> fillBag) = 0;
        virtual void Deleted(IEntity e) = 0;
        virtual void Clean() = 0;
    };
}