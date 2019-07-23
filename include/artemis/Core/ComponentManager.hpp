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
#include <vector>
#include "Exceptions.hpp"
#include "IManager.hpp"
#include "IEntity.hpp"
#include "IComponent.hpp"
#include "IComponentType.hpp"
#include "IComponentPool.hpp"
#include "ComponentTypeFactory.hpp"

namespace artemis 
{
    using namespace std;
    
    class Manager;
    class ComponentManager : public IComponentManager
    {
        vector<vector<IComponent*>> mComponentsByType;
        IComponentPool* mPooledComponents;
        vector<IEntity*> mDeleted;

        public:
        ComponentManager(){}
        ~ComponentManager(){}
        /**
         * Removes all components from the entity associated in this manager.
         *
         * @param e
         *			the entity to remove components from
        */
        private:
        void RemoveComponentsOfEntity(IEntity* e) 
        {
            auto componentBits = e->ComponentBits;
            for (auto i=0; i<componentBits.size(); i++) {
            // for (auto i = componentBits.NextSetBit(0); i >= 0; i = componentBits.NextSetBit(i+1)) {

                switch(TypeFactory.GetTaxonomy(i)) {

                case Taxonomy::BASIC:
                    mComponentsByType[i][e->Id()] = nullptr;
                    break;

                // case Taxonomy.POOLED:
                //     auto pooled = componentsByType[i][e.Id];
                //     pooledComponents.FreeByIndex((PooledComponent)pooled, i);
                //     componentsByType[i].set(e.Id, null);
                //     break;

                default:
                    throw exceptions::InvalidComponent("unknown component type %s", 
                    (TypeFactory.GetTaxonomy(i) == Taxonomy::BASIC ? "Basic" : "Pooled" ));

                }
            }
            componentBits.reset();
        }
    

        public:
        void AddComponent(IEntity* e, IComponentType* type, IComponent* component) 
        {
            mComponentsByType.reserve(type->GetIndex());

            vector<IComponent*> components = mComponentsByType[type->GetIndex()];
            if(components.size() == 0) {
                components = vector<IComponent*>();
                mComponentsByType[type->GetIndex()] = components;
            }
            
            components[e->Id()] = component;
            e->ComponentBits[type->GetIndex()] = true;
        }


        /**
         * Removes the component of given type from the entity.
         *
         * @param e
         *			the entity to remove from
        * @param type
        *			the type of component being removed
        */
        void RemoveComponent(IEntity* e, IComponentType *type) 
        {
            auto index = type->GetIndex();
            switch (type->GetTaxonomy()) {
            case Taxonomy::BASIC:
                mComponentsByType[index][e->Id()] = nullptr;
                e->ComponentBits.reset(type->GetIndex());
                break;
            // case Taxonomy::POOLED:
            //     auto pooled = mComponentsByType[index][e->Id()];
            //     e.ComponentBits.Clear(type->GetIndex());
            //     mPooledComponents.Free((PooledComponent)pooled, type);
            //     mComponentsByType[index][e->Id()] = nullptr;
            //     break;
            default:
                throw exceptions::InvalidComponent("unknown component type %s",
                (type->GetTaxonomy() == Taxonomy::BASIC ? "Basic" : "Pooled" ));
            }
        }
    
        /**
         * Get all components from all entities for a given type.
         *
         * @param type
         *			the type of components to get
        * @return a bag containing all components of the given type
        */
        vector<IComponent*>* GetComponentsByType(IComponentType *type) 
        {
            vector<IComponent*>* components = &mComponentsByType[type->GetIndex()];
            // if(components == nullptr) {
            //     components = new vector<IComponent*>();
            //     mComponentsByType[type->GetIndex()] = components;
            // }
            return components;
        }
    
        /**
         * Get a component of an entity.
         *
         * @param e
         *			the entity associated with the component
        * @param type
        *			the type of component to get
        * @return the component of given type
        */
        IComponent* GetComponent(IEntity* e, IComponentType *type) 
        {
            vector<IComponent*> components = mComponentsByType[type->GetIndex()];
            // if(components != nullptr) {
            //     return components[e->Id()];
            // }
            // return nullptr;
            return components[e->Id()];
        }
    
        /**
         * Get all component associated with an entity.
         *
         * @param e
         *			the entity to get components from
        * @param fillBag
        *			a bag to be filled with components
        * @return the {@code fillBag}, filled with the entities components
        */
        vector<IComponent*>* GetComponentsFor(IEntity* e,  vector<IComponent*>* fillBag) 
        {
            auto componentBits = e->ComponentBits;

            // for (auto i = componentBits.NextSetBit(0); i >= 0; i = componentBits.NextSetBit(i+1)) {
            for (auto i=0; i<componentBits.size(); i++) {   
                auto c = mComponentsByType[i][e->Id()];

                fillBag->push_back(c);
            }
            
            return fillBag;
        }

        
        
        void Deleted(IEntity* e)
        {
            mDeleted.push_back(e);
        }
        
        void Clean() 
        {
            if(mDeleted.size() > 0) {
                for(auto i = 0; mDeleted.size() > i; i++) {
                    RemoveComponentsOfEntity(mDeleted[i]);
                }
                mDeleted.clear();
            }
        }


    };
}