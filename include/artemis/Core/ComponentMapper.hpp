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
#include "vector"
#include "IType.hpp"
#include "IWorld.hpp"
#include "IEntity.hpp"
#include "IComponentMapper.hpp"
#include "IComponentType.hpp"
#include "IComponent.hpp"

namespace artemis 
{
    using namespace std;
    class IWorld;
    class IComponentType;
    class IComponent;
    class IEntity;
    class IComponentMapper;

    /**
     * High performance component retrieval from entities. Use this wherever you
     * need to retrieve components from entities often and fast.
     * 
     * @author Arni Arent
     *
     * @param <A> the class type of the component
     */
    class ComponentMapper : public IComponentMapper {
        IComponentType* mType;
        type_index mClassType;
        vector<IComponent*>* mComponents;

        public:

        explicit ComponentMapper(type_index type, IWorld* world) : mClassType(type)
        {
              mType = world->GetComponentManager()->TypeFactory.GetTypeFor(type);
              mComponents = world->GetComponentManager()->GetComponentsByType(mType);
        }
        ~ComponentMapper(){}

        /**
         * Fast but unsafe retrieval of a component for this entity.
         * No bounding checks, so this could throw an ArrayIndexOutOfBoundsExeption,
         * however in most scenarios you already know the entity possesses this component.
         * 
         * @param e the entity that should possess the component
         * @return the instance of the component
         */
        IComponent* Get(IEntity* e)
        {
            return mComponents->data()[e->Id()];
        }

        /**
         * Fast and safe retrieval of a component for this entity.
         * If the entity does not have this component then null is returned.
         * 
         * @param e the entity that should possess the component
         * @return the instance of the component
         */
        IComponent* GetSafe(IEntity* e)
        {
            return mComponents->at(e->Id());
        }

        /**
         * Checks if the entity has this type of component.
         * @param e the entity to check
         * @return true if the entity has this component type, false if it doesn't.
         */
        bool Has(IEntity* e)
        {
            return GetSafe(e) != nullptr;		
        }

        /**
         * Returns a component mapper for this type of components.
         * 
         * @param type the type of components this mapper uses.
         * @param world the world that this component mapper should use.
         * @return a new mapper.
         */
        IComponentMapper* GetFor(type_index type, IWorld* world)
        {
            return new ComponentMapper(type, world);
        }

    };
}