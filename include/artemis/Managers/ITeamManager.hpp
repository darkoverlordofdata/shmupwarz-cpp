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
#include "../Core/IManager.hpp"

namespace artemis::managers
{
    using namespace std;
    using namespace artemis;
    class IManager;
    // class IEntity;

    class ITeamManager : public artemis::IManager 
    {
        protected:
        unordered_map<string, vector<string>*> mPlayersByTeam;
        unordered_map<string, string> mTeamByPlayer;
        public:
		~ITeamManager(){}
        string GetTeam(string player) {}
        void SetTeam(string player, string team) {}
        vector<string>* GetPlayers(string team)  {}
        void RemoveFromTeam(string player) {}

    };
}