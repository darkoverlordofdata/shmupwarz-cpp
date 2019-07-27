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
    using namespace std;
    /**
     *  ComponentFactory
     * 
     *  dynamically create component by name 
     * 
     */
    class ComponentFactory 
    {
        /**
         * Component creation functor delegate
         */
        typedef Component* Delegate(); 
        /**
         * Registery of delegates by name
         */
        typedef map<string, Delegate*> Registry; 
        /**
         * Get the registry singleton
         */
        static Registry& Types() 
        {
            static Registry Types; 
            return Types; 
        }

        /**
         * Register component type T
         */
        template<class T> class Register 
        {
            /**
             * Creation functor
             */
            static Component* Create() 
            { 
                return new T(); 
            };

            /**
             * Set the creation functor in the types map
             */
            static Delegate* Type(const string& name) 
            { 
                return Types()[name] = Create; 
            }

            static Delegate* Factory;
        };

        public:
        /**
         * Create instance of component by name
         */
        static Component* New(const string& name) 
        { 
            const Registry::const_iterator iter = Types().find(name);
            return iter == Types().end() ? 0 : (*iter->second)(); 
        }

    };

}
