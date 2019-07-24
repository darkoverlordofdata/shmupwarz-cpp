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
#include "IntervalEntitySystem.hpp"

namespace artemis::systems 
{
    using namespace std;
    using namespace artemis;

    class IntervalEntitySystem;
	/**
	 * If you need to process entities at a certain interval then use this.
	 * A typical usage would be to regenerate ammo or health at certain intervals, no need
	 * to do that every game loop, but perhaps every 100 ms. or every second.
	 *
	 * @author Arni Arent
	 *
	 */
    class IntervalEntityProcessingSystem : public IntervalEntitySystem {

		public:
        IntervalEntityProcessingSystem(artemis::IAspect* aspect, float interval) 
        : IntervalEntitySystem(aspect, interval) { }

		/**
		* Process a entity this system is interested in.
		* @param e the entity to process.
		*/
		virtual void ProcessEach(IEntity* e) = 0;

		protected:
        void ProcessEntities(vector<IEntity*>* entities) 
		{
			for (auto entity : *entities)
				ProcessEach(entity);
		}

    };
}