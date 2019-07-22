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
#include "ComponentType.hpp"
#include <vector>

namespace artemis 
{
    using namespace std;

    class ComponentTypeFactory {
        private:
        /**
         * Contains all generated component types, newly generated component types
         * will be stored here.
         */
        unordered_map<string, ComponentType*> mComponentTypes;

        /** Amount of generated component types. */
        int mComponentTypeCount = 0;

        /** Index of this component type in componentTypes. */
        vector<ComponentType*> mTypes;

        public:
        ComponentTypeFactory() 
        {
            // Aspect.TypeFactory = this;
        }
        ~ComponentTypeFactory() {}

        /**
         * Gets the component type for the given component class.
         * <p>
         * If no component type exists yet, a new one will be created and stored
         * for later retrieval.
         * </p>
         *
         * @param c the component's class to get the type for
         * @return the component's {@link ComponentType}
         */
        ComponentType* GetTypeFor(const type_info& c) 
        {
            auto entry = mComponentTypes.find(c.name());
            if (entry == mComponentTypes.end()) 
            {
                auto type = new ComponentType(c);
                auto index = type->GetIndex();
                mComponentTypes[c.name()] = type;
                mTypes[index] = type;
                return type;
            } else 
                return entry->second;
        }

        /**
         * Get the index of the component type of given component class.
         *
         * @param c the component class to get the type index for
         * @return the component type's index
         */
        int GetIndexFor(type_info& c) 
        {
            return GetTypeFor(c)->GetIndex();
        }
    
        Taxonomy GetTaxonomy(int index) 
        {
            return mTypes[index]->GetTaxonomy();
        }


    };
}