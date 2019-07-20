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
#include "IEntitySystem.hpp"
#include "IEntityManager.hpp"
#include "IComponentManager.hpp"
#include "IEntityObserver.hpp"
#include "IFactory.hpp"

namespace artemis 
{

    typedef void (*Performer) (IEntityObserver* observer, IEntity* e);

    using namespace std;
    
    class World {

        private:
        IEntityManager mEntityManager;
        IComponentManager mComponentManager;
        float mDelta;
        vector<IEntity*> mAdded;
        vector<IEntity*> mChanged;
        vector<IEntity*> mDeleted;
        vector<IEntity*> mEnable;
        vector<IEntity*> mDisable;

        unordered_map<TypeInfoRef, IManager*, Hasher, EqualTo> mManagers;
        vector<IManager*> mManagersBag;
         
        unordered_map<TypeInfoRef, IEntitySystem*, Hasher, EqualTo> mSystems;
        vector<IEntitySystem*> mSystemsBag;

        IFactory* mFactory;
        

        public:
        World() 
        {
            SetManager(&mComponentManager);
            SetManager(&mEntityManager);
        }

        ~World() {}

        /**
         * Links in the IFactory instance.
         * Makes sure all managers systems are initialized in the order they were added.
         */
        void Initialize(IFactory* factory) 
        {
            mFactory = factory;
            for (auto manager : mManagersBag) {
                manager->Initialize(factory);
            }

        }

        /**
         * Returns a manager that takes care of all the entities in the world.
         * entities of this world.
         * 
         * @return entity manager.
         */
        IEntityManager * GetEntityManager() 
        {
            return &mEntityManager;
        }

        /**
         * Returns a manager that takes care of all the components in the world.
         * 
         * @return component manager.
         */
        IComponentManager * GetComponentManager() 
        {
            return &mComponentManager;
        }

        /**
         * Add a manager into this world. It can be retrieved later.
         * World will notify this manager of changes to entity.
         * 
         * @param manager to be added
         */
        IManager* SetManager(IManager * manager) 
        {
            mManagers[typeid(manager)] = manager;
            mManagersBag.push_back(manager);
            manager->SetWorld(this);
            return manager;
        }

        /**
         * Returns a manager of the specified type.
         * 
         * @param <T>
         * @param typeid of manager
         * @return the manager
         */
        // template<typename T>
        // T* GetManager(type_info& managerType)
        IManager* GetManager(type_info& managerType)
        {
            return mManagers[managerType];
        }

        /**
         * Deletes the manager from this world.
         * @param manager to delete.
         */
        void DeleteManager(IManager* manager) 
        {
            mManagers.erase(typeid(manager));
            // mManagersBag.erase(find(mManagersBag.begin(), mManagersBag.end(), manager));
            vector<Manager*>::iterator it = find(mManagersBag.begin(), mManagersBag.end(), manager);
            if (it != mManagersBag.end()) {
                mManagersBag.erase(it);
            }

        }

        /**
         * Time since last game loop.
         * 
         * @return delta time since last game loop.
         */
        float GetDelta() 
        {
            return mDelta;
        }

        /**
         * You must specify the delta for the game here.
         * 
         * @param delta time since last game loop.
         */
        void SetDelta(float delta) 
        {
            mDelta = delta;
        }

        /**
         * Adds a entity to this world.
         * 
         * @param e entity
         */
        void AddEntity(IEntity * e) 
        {
            mAdded.push_back(e);
        }

        /**
         * Ensure all systems are notified of changes to this entity.
         * If you're adding a component to an entity after it's been
         * added to the world, then you need to invoke this method.
         * 
         * @param e entity
         */
        void ChangedEntity(IEntity * e) 
        {
            mChanged.push_back(e);
        }

        /**
         * Delete the entity from the world.
         * 
         * @param e entity
         */
        void DeleteEntity(IEntity * e) 
        {
            if (find(mDeleted.begin(), mDeleted.end(), e) == mDeleted.end())
            {
                mDeleted.push_back(e);
            }
        }

        /**
         * (Re)enable the entity in the world, after it having being disabled.
         * Won't do anything unless it was already disabled.
         */ 
        void Enable(IEntity * e) 
        {
            mEnable.push_back(e);
        }

        /**
         * Disable the entity from being processed. Won't delete it, it will
         * continue to exist but won't get processed.
         */
        void Disable(IEntity * e) 
        {
            mDisable.push_back(e);
        }

        /**
         * Create and return a new or reused entity instance.
         * Will NOT add the entity to the world, use World.addEntity(Entity) for that.
         *
         * @param name optional name for debugging
         * @return entity
         */
        IEntity* CreateEntity(string name="") 
        {
            return mEntityManager.CreateEntityInstance(name);
        }

        /**
         * Get a entity having the specified id.
        * 
        * @param entityId
        * @return entity
        */
        IEntity* GetEntity(int entityId) 
        {
            return mEntityManager.GetEntity(entityId);
        }

        /**
         * Gives you all the systems in this world for possible iteration.
        * 
        * @return all entity systems in world.
        */
        vector<IEntitySystem*>* GetSystems() 
        {
            return &mSystemsBag;
        }

        /**
         * Will add a system to this world.
        *  
        * @param system the system to add.
        * @param passive wether or not this system will be processed by World.process()
        * @return the added system.
        */
        IEntitySystem* SetSystem(IEntitySystem* system, bool passive=false)
        {
            system->SetWorld(this);
            system->SetPassive(passive);
            
            mSystems[typeid(system)] = system;
            mSystemsBag.push_back(system);
            
            return system;
        }

        /**
         * Removed the specified system from the world.
        * @param system to be deleted from world.
        */
        void DeleteSystem(IEntitySystem* system) 
        {
            mSystems.erase(typeid(system));

            vector<EntitySystem*>::iterator it = find(mSystemsBag.begin(), mSystemsBag.end(), system);
            if (it != mSystemsBag.end()) {
                mSystemsBag.erase(it);
            }
        }

        private:
        void NotifySystems(Performer perform, Entity* e) 
        {
            for (auto system : mSystemsBag)
                perform((IEntityObserver*)system, e);
        }
    
        void NotifyManagers(Performer perform, Entity* e) 
        {
            for (auto manager : mManagersBag)
                perform((IEntityObserver*)manager, e);
        }

        /**
         * Retrieve a system for specified system type.
        * 
        * @param type type of system.
        * @return instance of the system in this world.
        */
        public:
        IEntitySystem* GetSystem(type_info& type) 
        {
            return mSystems[type];
        }

        /**
         * Performs an action on each entity.
        * @param entities
        * @param performer
        */
        private:
        void Check(vector<IEntity*> entities, Performer perform) 
        {
            if (!entities.empty()) 
            {
                for (auto e : entities)
                {
                    NotifyManagers(perform, e);
                    NotifySystems(perform, e);
                }
                entities.clear();
            }
        }

        /**
         * Process all non-passive systems.
        */
        public:
        void Update() 
        {
            Check(mAdded,   [](IEntityObserver* o, Entity* e) { o->Added(e); });  
            Check(mChanged, [](IEntityObserver* o, Entity* e) { o->Changed(e); });  
            Check(mDisable, [](IEntityObserver* o, Entity* e) { o->Disabled(e); });  
            Check(mEnable,  [](IEntityObserver* o, Entity* e) { o->Enabled(e); });  
            Check(mDeleted, [](IEntityObserver* o, Entity* e) { o->Deleted(e); });  
            
            mComponentManager.Clean();

            for (auto system : mSystemsBag)
                if(!system->IsPassive()) 
                    system->Process();
        }

        void Draw()
        {
            for (auto system : mSystemsBag){
                if(system->IsPassive()) {
                    system->Process();
                }
            }
        }

    };
}