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
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include "IType.hpp"


namespace artemis 
{
    
    class Type : public IType
    {
        private:
        string mName;
        size_t mHashCode;
        type_index mType;
        static unordered_map<string, Type*> mTypes;

        public:
        explicit Type(type_index type) : mType(type) 
        {
            mName = type.name();
            mHashCode = type.hash_code();

        };        
        ~Type(){}
        
        string Name() override
        {
            return mName;
        }

        size_t HashCode() override
        {
            return mHashCode;
        }


    };
}