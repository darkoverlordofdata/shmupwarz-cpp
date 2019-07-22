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
#include "IWorld.hpp"
#include "IEntity.hpp"

namespace artemis 
{
    class IWorld;
    class IEntity;

    class IEntitySystem 
    {
        public:
        ~IEntitySystem(){}
        virtual void Check(IEntity* e) = 0;
        virtual void Process() = 0;
        virtual void Added(IEntity* e) = 0;
        virtual void Changed(IEntity* e) = 0;
        virtual void Deleted(IEntity* e) = 0;
        virtual void Disabled(IEntity* e) = 0;
        virtual void Enabled(IEntity* e) = 0;
        virtual void SetWorld(IWorld* world) = 0;
        virtual bool IsPassive() = 0;
        virtual void SetPassive(bool passive) = 0;

    };
}