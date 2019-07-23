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
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "../Core/IEntity.hpp"


#include "../Core/IManager.hpp"

namespace artemis::managers
{
    using namespace std;
    using namespace artemis;
    class IManager;

    class IGroupManager : public artemis::IManager 
    {
        protected:
        unordered_map<string, vector<IEntity*>*> mEntitiesByGroup;
        unordered_map<IEntity*, vector<string>*> mGroupsByEntity;
        public:
		~IGroupManager(){}
        void Add(IEntity* e, string group){};
        void Remove(IEntity* e, string group){};
        void RemoveFromAllGroups(IEntity* e){};
        vector<IEntity*>* GetEntities(string group){};
        vector<string>* GetGroups(IEntity* e){};
        bool IsInAnyGroup(IEntity* e){};
        bool IsInGroup(IEntity* e, string group){};
        void Deleted(IEntity* e){};

    };
}