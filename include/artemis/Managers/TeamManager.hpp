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
    /**
     * Use this class together with PlayerManager.
     *
     * You may sometimes want to create teams in your game, so that
     * some players are team mates.
     *
     * A player can only belong to a single team.
     *
     * @author Arni Arent
     *
     */
    class TeamManager : public artemis::IManager {
        protected:
        unordered_map<string, vector<string>*> mPlayersByTeam;
        unordered_map<string, string> mTeamByPlayer;

        public:
        string GetTeam(string player) {
            return mTeamByPlayer[player];
        }

        void SetTeam(string player, string team) {
            RemoveFromTeam(player);

            mTeamByPlayer[player] = team;

            auto players = mPlayersByTeam[team];
            if(players == nullptr) {
                players = new vector<string>();
                mPlayersByTeam[team] = players;
            }
            players->push_back(player);
        }

        vector<string>* GetPlayers(string team)  {
            return mPlayersByTeam[team];
        }

        void RemoveFromTeam(string player) {
            auto team = mTeamByPlayer[player];
            if (mTeamByPlayer.erase(player)) {
                auto players = mPlayersByTeam[team];
                if (players != nullptr) {
                    players->erase(find(players->begin(), players->end(), player));
                }
            }
        }

    };
}