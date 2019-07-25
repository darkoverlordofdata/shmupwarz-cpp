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
#include <map>
#include <string>
#include "Component.hpp"

namespace artemis 
{
  class ComponentFactory 
  {
        public:
        static Component* Create(const std::string& id) 
        { 
            const Types::const_iterator iter = types().find(id);
            return iter == types().end() ? 0 : (*iter->second)(); 
        }

        private:
        typedef Component* Factory(); 
        typedef std::map<std::string, Factory*> Types; 

        static Types& types() 
        {
            static Types _types; 
            return _types; 
        }

        template<class T = int> class Register 
        {
            static Component* Create() { 
            return new T(); 
        };

        static Factory* Initialize(const std::string& id) 
        { 
            return types()[id] = Create; 
        }

        static Factory* Creator;
    };
  };

}
