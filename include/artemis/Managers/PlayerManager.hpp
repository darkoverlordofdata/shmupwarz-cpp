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
#include "../IManager.hpp"

namespace artemis::managers
{
    using namespace std;
    using namespace artemis;
    class IManager;
    /**
     * You may sometimes want to specify to which player an entity belongs to.
     *
     * An entity can only belong to a single player at a time.
     *
     * @author Arni Arent
     *
     */
    class PlayerManager : public artemis::IManager {
        protected:
        unordered_map<IEntity*, string> mPlayerByEntity;
        unordered_map<string, vector<IEntity*>*> mEntitiesByPlayer;

        public:
        void SetPlayer(IEntity* e, string player) {
            mPlayerByEntity[e] = player;
            auto entities = mEntitiesByPlayer[player];
            if (entities == nullptr) {
                entities = new vector<IEntity*>();
                mEntitiesByPlayer[player] = entities;
            }
            entities->push_back(e);
        }

        vector<IEntity*>* GetEntitiesOfPlayer(string player)  {
            auto entities = mEntitiesByPlayer[player];
            if (entities == nullptr) {
                entities = new vector<IEntity*>();
            }
            return entities;
        }

        void RemoveFromPlayer(IEntity* e) {
            auto player = mPlayerByEntity[e];
            if (player != "") {
                auto entities = mEntitiesByPlayer[player];
                if(entities != nullptr) {
                    entities->erase(find(entities->begin(), entities->end(), e));
                }
            }
        }

        string GetPlayer(IEntity* e) {
            return mPlayerByEntity[e];
        }


        void Initialize() {}


        void Deleted(IEntity* e) {
            RemoveFromPlayer(e);
        }


    };
}