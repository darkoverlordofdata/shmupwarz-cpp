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
#include <exception>
#include <stdio.h>

namespace core::exceptions {

    using namespace std;

    class OverflowException : public exception {
        const char* what() const throw () {
            return "OverflowException";
        }
    };



    class RangeError : public exception {
        char buffer[1024];
        const char* msg;
        int n;
        public:
        RangeError(char* msg, int n) {
            this->msg = msg;
            this->n  = n;
        }
        const char* what() const throw () {
            snprintf((char*)buffer, sizeof(buffer), msg, n);
            return buffer;
        }
    };

}

