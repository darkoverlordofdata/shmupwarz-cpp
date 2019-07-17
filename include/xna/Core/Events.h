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
#include <vector>
#include <functional>
#include <memory>
// #include <iostream>
//https://github.com/rafeloken/event_system

namespace core {

    using std::vector;
    using std::nullptr_t;
    using std::unique_ptr;

    
    class EventHandler {
    public:
        using Func = std::function<void(void*, void*)>;

    private:
        Func mFunc;

    public:
        int mId;
        inline static int counter = 0;

        EventHandler(const Func &func) : mFunc{func} {
            this->mId = ++EventHandler::counter;
        }

        void operator()(void* sender, void* args) {
            mFunc(sender, args);
        }

        void operator=(const EventHandler &func) {
            if(mFunc == nullptr) {
                mFunc = func;
                mId = ++counter;
            } else {
                // Throw as exception or just log it out.
                // std::cerr << "Nope!" << std::endl;
            }
        }

        bool operator==(const EventHandler &del) {
            return mId == del.mId;
        }
        bool operator!=(nullptr_t) {
            return mFunc != nullptr;
        }


    };


    class Event {
        std::vector<std::unique_ptr<EventHandler>> mHandlers;

        // void NotifyHandlers(void*, void*);
    public:

        void NotifyHandlers(void* sender, void* args) {
            vector<unique_ptr<EventHandler>>::iterator func = mHandlers.begin();
            for(; func != mHandlers.end(); ++func) {
                if(*func != nullptr && (*func)->mId != 0) {            
                    (*(*func))(sender, args);
                    // std::cout << "EventHandler.mId: " << (*func)->mId << std::endl;
                }
            }
        }

        void AddHandler(const EventHandler &handler) {
            mHandlers.push_back(unique_ptr<EventHandler>(new EventHandler{handler}));
        }

        void RemoveHandler(const EventHandler &handler) {
            vector<unique_ptr<EventHandler>>::iterator to_remove = mHandlers.begin();
            for(; to_remove != mHandlers.end(); ++to_remove) {
                if(*(*to_remove) == handler) {
                    // std::cout << "Removing: " << (*to_remove)->mId << std::endl;
                    mHandlers.erase(to_remove);
                    break;
                }
            }
        }

        void operator()(void* sender, void* args) {
            NotifyHandlers(sender, args);
        }

        Event &operator+=(const EventHandler &handler) {
            AddHandler(handler);

            return *this;
        }

        Event &operator+=(const EventHandler::Func &handler) {
            AddHandler(EventHandler{handler});

            return *this;
        }

        Event &operator-=(const EventHandler &handler) {
            RemoveHandler(handler);

            return *this;
        }    

        int TotalHandlers() { return mHandlers.size(); }
    };


}