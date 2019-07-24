#pragma once
#include <vector>
#include <unordered_map>
#include <bitset>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <any>

namespace artemis {

    using namespace std;

    class BlackBoard
    {
        private:
        unordered_map<string, any>intelligence;

        public:
        template<class T>
        T GetEntry(string name) 
        {
            return any_cast<T>(intelligence[name]);
        }

        template<class T>
        void SetEntry(string name, T intel) 
        {
            intelligence[name] = any_cast<T>(intel);
        }

    };

}