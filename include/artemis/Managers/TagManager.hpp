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
#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "../IManager.hpp"

namespace artemis::managers
{
    using namespace std;
    using namespace artemis;
    class IManager;
    /**
     * If you need to tag any entity, use  A typical usage would be to tag
     * entities such as "PLAYER", "BOSS" or something that is very unique.
     *
     * @author Arni Arent
     *
     */
    class TagManager : public artemis::IManager {
        protected:
        unordered_map<string, IEntity*> mEntitiesByTag;
        unordered_map<IEntity*, string> mTagsByEntity;

        void Register(string tag, IEntity* e) {
            mEntitiesByTag[tag] = e;
            mTagsByEntity[e] = tag;
        }

        void Unregister(string tag) {
            mTagsByEntity.erase(mEntitiesByTag[tag]);
            mEntitiesByTag.erase(tag);
        }

        bool IsRegistered(string tag) {
            return mEntitiesByTag.find(tag) != mEntitiesByTag.end();
        }

        IEntity* GetEntity(string tag) {
            return mEntitiesByTag[tag];
        }

        vector<string>* GetRegisteredTags() {
            // return mTagsByEntity.Values.ToArray();
            auto values = new vector<string>();
            for(auto kv : mTagsByEntity) {
                values->push_back(kv.second);
            } 
            return values;            
        }

        void Deleted(IEntity* e) {
            mEntitiesByTag.erase(mTagsByEntity[e]);
            mTagsByEntity.erase(e);
        }

    };
}