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
#include "IFactory.hpp"

namespace artemis 
{
    class IWorld;
    class IFactory;
    class IManager {
        public:
        IWorld* mWorld;
        IFactory* mFactory;
        ~IManager(){}
        public:
        void Initialize(IFactory* factory)
        { 
            mFactory = factory; 
        }

        void SetWorld(IWorld * world)
        { 
            mWorld = world; 
        }

        IWorld* GetWorld()
        { 
            return mWorld; 
        }
        // void Initialize(IFactory* factory){};
        // IWorld* GetWorld(){};
        // void SetWorld(IWorld * world){};
		void Added(IEntity* e){};
		void Changed(IEntity* e){};
		void Deleted(IEntity* e){};
		void Disabled(IEntity* e){};
		void Enabled(IEntity* e){};

    };
}