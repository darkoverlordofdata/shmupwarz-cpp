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
#include <vector>
#include "IComponent.hpp"
#include "IType.hpp"
#include "IComponentType.hpp"
#include "IWorld.hpp"

namespace artemis 
{

    using namespace std;

    class IWorld;
    class IComponent;
    class IType;
    class IComponentType;

    class IEntity {
        public:
        ~IEntity(){}
        std::bitset<BITSIZE> ComponentBits;
        std::bitset<BITSIZE> SystemBits;


        virtual int Id() = 0;
        // virtual IComponent* CreateComponent(IType* type) = 0;
        virtual IEntity* AddComponent(IComponent* component) = 0;
        virtual IEntity* RemoveComponentInstance(IComponent* component) = 0;
        virtual IEntity* RemoveComponent(IComponentType* type) = 0;
        // virtual IEntity* RemoveComponentByType(IType* type) = 0;
        virtual bool IsActive() = 0;
        virtual bool IsEnabled() = 0;
        virtual IComponent* GetComponent(IComponentType* type) = 0;
        // virtual IComponent* GetComponentByType(IType* type) = 0;
        virtual vector<IComponent*>* GetComponents(vector<IComponent*>* fillBag) = 0;
        virtual void AddToWorld() = 0;
        virtual void ChangedInWorld() = 0;
        virtual void DeleteFromWorld() = 0;
        virtual void Enable() = 0;
        virtual void Disable() = 0;
        virtual IWorld* GetWorld() = 0;
    };
}