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
namespace artemis::utils {

    template<typename E>
    class ImmutableBag {
        public:
        virtual E Get(int index) = 0;
        virtual int GetCapacity() = 0;
        virtual int GetCount() = 0;
        virtual bool IsEmpty() = 0;
        virtual ~ImmutableBag(){};
    };
}