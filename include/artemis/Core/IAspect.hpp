#pragma once
#include <vector>
#include <bitset>
#include <typeinfo>
#include <cstdarg>
#include "IAspect.hpp"
#include "IWorld.hpp"

namespace artemis {
    using namespace std;
    class IWorld;
    class IAspect {
        public:
        ~IAspect(){}
        virtual void SetWorld(IWorld* world) = 0;
        virtual bitset<BITSIZE> GetAllSet() = 0;
        virtual bitset<BITSIZE> GetExclusionSet() = 0;
        virtual bitset<BITSIZE> GetOneSet() = 0;


    };
}

