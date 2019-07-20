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
#include "Manager.hpp"
#include "ComponentManager.hpp"
#include "Type.hpp"
#include <string>

namespace artemis 
{
    enum class Taxonomy 
    {
        BASIC, POOLED 
    };

    class ComponentType {
        private:
        inline static int INDEX = 0;
        int mIndex = 0;
        const type_info& mType;
        Taxonomy mTaxonomy;

        public:
        static ComponentManager componentManager;
        explicit ComponentType(const type_info& type) : mType(type) 
        {   
            mIndex = INDEX++;
            mTaxonomy = Taxonomy::BASIC;
        }

        ~ComponentType() {}

        string GetName() 
        {
            return mType.name();
        }

        int GetIndex() 
        {
            return mIndex;
        }

        Taxonomy GetTaxonomy() 
        {
            return mTaxonomy;
        }
        

    };
}