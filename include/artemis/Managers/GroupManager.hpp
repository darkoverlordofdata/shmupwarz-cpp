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

    class IManager;
    
    /**
     * If you need to group your entities together, e.g. tanks going into "units" group or explosions into "effects",
     * then use this manager. You must retrieve it using world instance.
     *
     * A entity can be assigned to more than one group.
     *
     * @author Arni Arent
     *
     */
    class GroupManager : public artemis::IManager {

        protected:
        unordered_map<string, vector<IEntity*>*> mEntitiesByGroup;
        unordered_map<IEntity*, vector<string>*> mGroupsByEntity;
        /**
         * Set the group of the entity.
        *
        * @param group group to add the entity into.
        * @param e entity to add into the group.
        */
        void Add(IEntity* e, string group) {
            auto entities = mEntitiesByGroup[group];
            if (entities == nullptr) {
                entities = new vector<IEntity*>();
                mEntitiesByGroup[group] = entities;
            }
            entities->push_back(e);

            auto groups = mGroupsByEntity[e];
            if (groups == nullptr) {
                groups = new vector<string>();
                mGroupsByEntity[e] = groups;
            }
            groups->push_back(group);
        }

        /**
         * Remove the entity from the specified group.
        * @param e
        * @param group
        */
        void Remove(IEntity* e, string group) {
            auto entities = mEntitiesByGroup[group];
            if (entities != nullptr) {
                entities->erase(find(entities->begin(), entities->end(), e));
            }

            auto groups = mGroupsByEntity[e];
            if (groups != nullptr) {
                groups->erase(find(groups->begin(), groups->end(), group));
            }
        }

        void RemoveFromAllGroups(IEntity* e) {
            auto groups = mGroupsByEntity[e];
            if (groups != nullptr) {
                for(auto i = 0, s = (int)groups->size(); s > i; i++) {
                    auto entities = mEntitiesByGroup[groups->at(i)];
                    if(entities != nullptr) {
                        entities->erase(find(entities->begin(), entities->end(), e));
                    }
                }
                groups->clear();
            }
        }

        /**
         * Get all entities that belong to the provided group.
        * @param group name of the group.
        * @return read-only bag of entities belonging to the group.
        */
        vector<IEntity*>* GetEntities(string group) {
            auto entities = mEntitiesByGroup[group];
            if (entities == nullptr) {
                entities = new vector<IEntity*>();
                mEntitiesByGroup[group] = entities;
            }
            return entities;
        }

        /**
         * @param e entity
        * @return the groups the entity belongs to, nullptr if none.
        */
        vector<string>* GetGroups(IEntity* e)  {
            return mGroupsByEntity[e];
        }

        /**
         * Checks if the entity belongs to any group.
        * @param e the entity to check.
        * @return true if it is in any group, false if none.
        */
        bool IsInAnyGroup(IEntity* e) {
            return GetGroups(e) != nullptr;
        }

        /**
         * Check if the entity is in the supplied group.
        * @param group the group to check in.
        * @param e the entity to check for.
        * @return true if the entity is in the supplied group, false if not.
        */
        bool IsInGroup(IEntity* e, string group) {
            if (group != "") {
                auto groups = mGroupsByEntity[e];
                for(auto i = 0, s = (int)groups->size(); s > i; i++) {
                    auto g = groups->at(i);
                    if (group == g) {
                        return true;
                    }
                }
            }
            return false;
        }


        void Deleted(IEntity* e) {
            RemoveFromAllGroups(e);
        }


    };
}