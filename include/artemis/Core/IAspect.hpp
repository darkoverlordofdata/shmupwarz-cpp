#pragma once
#include "IType.hpp"
#include "IWorld.hpp"
#include <bitset>

namespace artemis {
    using namespace std;
    class IWorld;
    class IType;
    class IAspect {
        public:
        ~IAspect(){}
        virtual void SetWorld(IWorld world) = 0;
        virtual bitset<BITSIZE> GetAllSet() = 0;
        virtual bitset<BITSIZE> GetExclusionSet() = 0;
        virtual bitset<BITSIZE> GetOneSet() = 0;
        virtual IAspect* All(IType** types) = 0;
        virtual IAspect* Exclude(IType** types) = 0;
        virtual IAspect* One(IType** types) = 0;


    };
}

