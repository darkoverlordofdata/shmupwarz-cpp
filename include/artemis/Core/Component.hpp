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
#include "../IComponent.hpp"

namespace artemis 
{


    /**
     * A tag class. All components in the system must extend this class.
     * 
     * @author Arni Arent
     */
    class Component : public IComponent 
    {
        public: 
        virtual ~Component() {}

        static Component* Create(const std::string& id) 
        { 
            const Creators_t::const_iterator iter = static_creators().find(id);
            return iter == static_creators().end() ? 0 : (*iter->second)(); 
        }

        private:
        typedef Component* Creator_t(); 
        typedef std::map<std::string, Creator_t*> Creators_t; 

        static Creators_t& static_creators() 
        {
            static Creators_t s_creators; 
            return s_creators; 
        } 

        template<class T = int> class Register 
        {
            static Component* Create() 
            { 
                return new T(); 
            };
            static Creator_t* Init_creator(const std::string& id) 
            { 
                return static_creators()[id] = Create; 
            }
            static Creator_t* Creator;
        };



    };


}