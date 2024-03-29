#pragma once
#include <vector>
#include <bitset>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <cstdarg>
#include "../IAspect.hpp"
#include "../IWorld.hpp"

namespace artemis {

    using namespace std;

    class IWorld;
    class IAspect;

    /**
     * An Aspects is used by systems as a matcher against entities, to check if a system is
     * interested in an entity. Aspects define what sort of component types an entity must
     * possess, or not possess.
     *
     * This creates an aspect where an entity must possess A and B and C:
     * Aspect.getAspectForAll(A.class, B.class, C.class)
     *
     * This creates an aspect where an entity must possess A and B and C, but must not possess U or V.
     * Aspect.getAspectForAll(A.class, B.class, C.class).exclude(U.class, V.class)
     *
     * This creates an aspect where an entity must possess A and B and C, but must not possess U or V, but must possess one of X or Y or Z.
     * Aspect.getAspectForAll(A.class, B.class, C.class).exclude(U.class, V.class).one(X.class, Y.class, Z.class)
     *
     * You can create and compose aspects in many ways:
     * Aspect.getEmpty().one(X.class, Y.class, Z.class).all(A.class, B.class, C.class).exclude(U.class, V.class)
     * is the same as:
     * Aspect.getAspectForAll(A.class, B.class, C.class).exclude(U.class, V.class).one(X.class, Y.class, Z.class)
     *
     * @author Arni Arent
     *
     */
    class Aspect : public IAspect {
        private:
        bitset<BITSIZE> mAllSet;
        bitset<BITSIZE> mExclusionSet;
        bitset<BITSIZE> mOneSet;
        IWorld* mWorld;
        
        static ComponentTypeFactory TypeFactory;

        public:
        /**
         *
         * @param {artemis.World} world
         */
        void SetWorld(IWorld* world) override
        {
            mWorld = world;
        }

        bitset<BITSIZE> GetAllSet() override
        {
            return mAllSet;
        }

        bitset<BITSIZE> GetExclusionSet() override
        {
            return mExclusionSet;
        }

        bitset<BITSIZE> GetOneSet() override
        {
            return mOneSet;
        }



        /**
         * Returns an aspect where an entity must possess all of the specified component types.
         * @param {Type} type a required component type
         * @param {Array<Type>} types a required component type
         * @return {artemis.Aspect} an aspect that can be matched against entities
         */
        template<class ... Types>
        IAspect* All(Types ... types)
        {
            for (type_index type : { types...})
            {
                auto index = Aspect::TypeFactory.GetIndexFor(type);
                mAllSet[index] = true;
            }

            return this;
        }

        /**
         * Excludes all of the specified component types from the aspect. A system will not be
         * interested in an entity that possesses one of the specified exclusion component types.
         *
         * @param {Type} type component type to exclude
         * @param {Array<Type>} types component type to exclude
         * @return {artemis.Aspect} an aspect that can be matched against entities
         */
        template<class ... Types>
        IAspect* Exclude(Types ... types)
        {
            for (type_index type : { types...})
            {
                auto index = Aspect::TypeFactory.GetIndexFor(type);
                mExclusionSet[index] = true;
            }

            return this;

        }

        /**
         * Returns an aspect where an entity must possess one of the specified component types.
         * @param {Type} type one of the types the entity must possess
         * @param {Array<Type>} types one of the types the entity must possess
         * @return {artemis.Aspect} an aspect that can be matched against entities
         */
        template<class ... Types>
        IAspect* One(Types ... types)
        {
            for (type_index type : { types...})
            {
                auto index = Aspect::TypeFactory.GetIndexFor(type);
                mOneSet[index] = true;
            }

            return this;

        }

        /**
         * Creates an aspect where an entity must possess all of the specified component types.
         *
         * @param {Type} type the type the entity must possess
         * @param {Array<Type>} types the type the entity must possess
         * @return {artemis.Aspect} an aspect that can be matched against entities
         *
         * @deprecated
         * @see getAspectForAll
         */
        template<class ... Types>
        static IAspect* GetAspectFor(Types ... types) 
        {
            auto aspect = new Aspect();
            for (type_index type : { types...})
            {
                auto index = Aspect::TypeFactory.GetIndexFor(type);
                aspect->mAllSet[index] = true;
            }
            return aspect;
        }

        /**
         * Creates an aspect where an entity must possess all of the specified component types.
         *
         * @param {Type} type a required component type
         * @param {Array<Type>} types a required component type
         * @return {artemis.Aspect} an aspect that can be matched against entities
         */
        template<class ... Types>
        static IAspect* GetAspectForAll(Types ... types) 
        {
            auto aspect = new Aspect();
            for (type_index type : { types...})
            {
                auto index = Aspect::TypeFactory.GetIndexFor(type);
                aspect->mAllSet[index] = true;
            }
            return aspect;
        }
        
        /**
         * Creates an aspect where an entity must possess one of the specified component types.
         *
         * @param {Type} type one of the types the entity must possess
         * @param {Array<Type>} types one of the types the entity must possess
         * @return {artemis.Aspect} an aspect that can be matched against entities
         */
        template<class ... Types>
        static IAspect* GetAspectForOne(Types ... types) 
        {
            auto aspect = new Aspect();
            for (type_index type : { types...})
            {
                auto index = Aspect::TypeFactory.GetIndexFor(type);
                aspect->mOneSet[index] = true;
            }
            return aspect;
        }
    
        /**
         * Creates and returns an empty aspect. This can be used if you want a system that processes no entities, but
         * still gets invoked. Typical usages is when you need to create special purpose systems for debug rendering,
         * like rendering FPS, how many entities are active in the world, etc.
         *
         * You can also use the all, one and exclude methods on this aspect, so if you wanted to create a system that
         * processes only entities possessing just one of the components A or B or C, then you can do:
         * Aspect.getEmpty().one(A,B,C);
         *
         * @return {artemis.Aspect} an empty Aspect that will reject all entities.
         */
        static IAspect* GetEmpty() 
        {
            auto aspect = new Aspect();
            return aspect;
        }

    };
}

