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
#include <string>
#include <bitset>
#include "IEntity.hpp"
#include "World.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "IComponentType.hpp"

namespace artemis 
{

    using namespace std;

    class EntityManager;
    class World;
    
    class Entity : public IEntity {
        private:
        string mName;
        int mId;
        // bitset<BITSIZE> mComponentBits;
        // bitset<BITSIZE> mSystemBits;
        World * mWorld;
        EntityManager mEntityManager;
        ComponentManager mComponentManager;

        public:
        string Name() { return mName; }
        // bitset<BITSIZE> ComponentBits() { return mComponentBits; }
        // bitset<BITSIZE> SystemBits() { return mSystemBits; }

        Entity(World* world, int id, string name="") {
            mWorld = world;
            mId = id;
            mName = name;
        }

        int Id()
        {
            return mId;
        }

        /**
         * Make entity ready for re-use.
        * Will generate a new uuid for the entity.
        */
        void Reset() 
        {
            SystemBits.reset();
            ComponentBits.reset();
            // uuid = UUID.RandomUUID();
        }

        /**
         * Add a component to this entity.
         * 
         * @param component to add to this entity
         * @return this entity for chaining.
         */
        IEntity* AddComponent(IComponent* component, ...) 
        {

            auto tf = mWorld->GetComponentManager()->TypeFactory;
            auto componentType = tf.GetTypeFor(typeof(component));
            ComponentBits.set(componentType->GetIndex(), true);
            mComponentManager.AddComponent(this, componentType, component);
            return this;
        }

        private:
        ComponentType* GetTypeFor(type_index c) 
        {
            return mWorld->GetComponentManager()->TypeFactory.GetTypeFor(c);
        }

        public:
        /**
         * Removes the component from this entity.
         * 
         * @param component to remove from this entity.
         * @return this entity for chaining.
         */
        IEntity* RemoveComponentInstance(IComponent* component) 
        {
            RemoveComponent(GetTypeFor(typeof(component)));
            return this;
        }

        /**
         * Faster removal of components from a entity.
         * 
         * @param type to remove from this entity.
         * @return this entity for chaining.
         */
        IEntity* RemoveComponent(IComponentType* type) 
        {
            mComponentManager.RemoveComponent(this, type);
            return this;
        }

        /**
         * Remove component by its type.
         * @param type
         * 
         * @return this entity for chaining.
         */
        IEntity* RemoveComponentByType(type_index type) 
        {
            RemoveComponent(GetTypeFor(type));
            return this;
        }

        /**
         * Checks if the entity has been added to the world and has not been deleted from it.
         * If the entity has been disabled this will still return true.
         * 
         * @return if it's active.
         */
        bool IsActive() 
        {
            return mEntityManager.IsActive(mId);
        }
          
        /**
         * Will check if the entity is enabled in the world.
         * By default all entities that are added to world are enabled,
         * this will only return false if an entity has been explicitly disabled.
         * 
         * @return if it's enabled
         */
        bool IsEnabled() 
        {
            return mEntityManager.IsEnabled(mId);
        }

        /**
         * This is the preferred method to use when retrieving a component from a
         * entity. It will provide good performance.
         * But the recommended way to retrieve components from an entity is using
         * the ComponentMapper.
         * 
         * @param type
         *            in order to retrieve the component fast you must provide a
         *            ComponentType instance for the expected component.
         * @return
         */
        IComponent* GetComponent(IComponentType* type) 
        {
            return mComponentManager.GetComponent(this, type);
        }

        /**
         * Slower retrieval of components from this entity. Minimize usage of this,
         * but is fine to use e.g. when creating new entities and setting data in
         * components.
         * 
         * @param <T>
         *            the expected return component type.
         * @param type
         *            the expected return component type.
         * @return component that matches, or null if none is found.
         */
        IComponent* GetComponentByType(type_index type) 
        {
            return mComponentManager.GetComponent(this, GetTypeFor(type));
        }

        /**
         * Returns a bag of all components this entity has.
         * You need to reset the bag yourself if you intend to fill it more than once.
         * 
         * @param fillBag the bag to put the components into.
         * @return the fillBag with the components in.
         */
        vector<IComponent*>* GetComponents(vector<IComponent*>* fillBag) 
        {
            return mComponentManager.GetComponentsFor(this, fillBag);
        }

        /**
         * Refresh all changes to components for this entity. After adding or
         * removing components, you must call this method. It will update all
         * relevant systems. It is typical to call this after adding components to a
         * newly created entity.
         */
        void AddToWorld() 
        {
            mWorld->AddEntity(this);
        }
          
        /**
         * This entity has changed, a component added or deleted.
        */
        void ChangedInWorld() 
        {
            mWorld->ChangedEntity(this);
        }

        /**
         * Delete this entity from the world.
         */
        void DeleteFromWorld() 
        {
            mWorld->DeleteEntity(this);
        }
          
        /**
         * (Re)enable the entity in the world, after it having being disabled.
         * Won't do anything unless it was already disabled.
         */
        void Enable() 
        {
            mWorld->Enable(this);
        }
          
        /**
         * Disable the entity from being processed. Won't delete it, it will
         * continue to exist but won't get processed.
         */
        void Disable() 
        {
            mWorld->Disable(this);
        }

        /**
         * Returns the world this entity belongs to.
        * @return world of entity.
        */
        IWorld* GetWorld() 
        {
            return mWorld;
        }
      
    };
}