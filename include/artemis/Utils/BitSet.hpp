#pragma once
#include <cstdint>
#include <algorithm>
#include "core/Core.hpp"

namespace artemis::utils {

    /*
    * BitSets are packed into arrays of "words."  Currently a word
    * consists of 32 bits, requiring 5 address bits.
    */
    const int ADDRESS_BITS_PER_WORD = 5;
    const int BITS_PER_WORD = 1 << ADDRESS_BITS_PER_WORD; // 32
    const int64_t WORD_MASK = 0xffffffff;
    /**
     * @see http://stackoverflow.com/questions/6506356/java-implementation-of-long-numberoftrailingzeros
     */
    inline uint32_t NumberOfTrailingZeros(uint32_t i) 
    {
        if (i == 0) return 32;  
        uint32_t x = i;
        uint32_t y;
        uint32_t n = 31;
        y = x << 16; if (y != 0) { n -= 16; x = y; }
        y = x <<  8; if (y != 0) { n -=  8; x = y; }
        y = x <<  4; if (y != 0) { n -=  4; x = y; }
        y = x <<  2; if (y != 0) { n -=  2; x = y; }
        return (n - ((x << 1) >> 31));
    }

    class BitSet {
        public:

        uint32_t* words;
        int wordsLength;

        /**
         * constructor
         */
        BitSet(int nbits=0) 
        {
            if (nbits < 0) 
            {
                throw core::exceptions::RangeError("Negative Array Size: [%n]", nbits);
            } 
            else if (nbits == 0) 
            {
                words = new uint32_t[0];
            } 
            else 
            {
                wordsLength = (((nbits-1) >> ADDRESS_BITS_PER_WORD)+1);
                words = new uint[wordsLength];
                for (auto i=0, l = wordsLength; i<l; i++) 
                {
                    words[i] = 0;
                }
            }
        }

        ~BitSet() {}

        /**
         * NextSetBit
         * @paran fromIndex
         */
        int NextSetBit(int fromIndex) 
        {
            auto u = fromIndex >> ADDRESS_BITS_PER_WORD;
            auto wordsInUse = wordsLength;

            auto word = words[u] & (WORD_MASK << fromIndex);
            while (true) 
            {
                if (word != 0)
                    return (int)((u * BITS_PER_WORD) + NumberOfTrailingZeros(word));
                if (++u == wordsInUse)
                    return -1;
                word = words[u];
            }
        }

        /**
         * Intersects
         * @param set
         * @returns true if the sets intersect
         */
        bool Intersects(BitSet* set) 
        {
            auto wordsInUse = wordsLength;

            for (auto i = std::min(wordsInUse, set->wordsLength) - 1; i >= 0; i--)
                if ((words[i] & set->words[i]) != 0)
                    return true;
            return false;

        }


        /**
         * IsEmpty
         * @returns true if this is empty
         */
        bool IsEmpty() 
        {
            return wordsLength == 0;
        }

        /**
         * Resize
         * @param array
         * @param old length
         * @param new length
         * @returns new array
         */
        uint32_t* Resize(uint32_t* w, int m, int n) {
        
            uint32_t* resized = new uint32_t[n];
            for (auto i=0; i<m; i++)
                resized[i] = w[i];
            for (auto i=m; i<n; i++)
                resized[i] = 0;
            delete [] w;
            return resized;
        }

        /**
         * Set
         * @param index
         * @param value
         */
        void Set(int bitIndex, bool value) 
        {
            auto wordIndex = bitIndex >> ADDRESS_BITS_PER_WORD;
            auto wordsInUse = wordsLength;
            auto wordsRequired = wordIndex+1;

            if (wordIndex >= wordsLength) 
            {
                words = Resize(words, wordIndex, wordIndex+1);
                // words.resize(wordIndex+1);
            }
            if (wordsInUse < wordsRequired) 
            {
                // words.resize(std::max(2 * wordsInUse, wordsRequired));
                words = Resize(words, wordIndex, std::max(2 * wordsInUse, wordsRequired));
                for (auto i=wordsInUse, l=wordsLength; i<l; i++) 
                {
                    words[i] = 0;
                }
            }

            if (value) 
            {
                words[wordIndex] |= (1 << bitIndex);
            } 
            else 
            {
                words[wordIndex] &= ~(1 << bitIndex);
            }
        }

        /**
         * Get
         * @param index
         * @returns value
         */
        bool Get(int bitIndex) 
        {
            auto wordIndex = bitIndex >> ADDRESS_BITS_PER_WORD;
            auto wordsInUse = wordsLength;

            return (wordIndex < wordsInUse) && ((words[wordIndex] & (1 << bitIndex)) != 0);
        }

        /**
         * Clear
         * @param index
         */
        void Clear(int bitIndex=-1)  
        {
            if (bitIndex == -1) 
            {
                auto wordsInUse = wordsLength;
                while (wordsInUse>0) 
                {
                    words[--wordsInUse] = 0;
                }
                return;
            }

            auto wordIndex = bitIndex >> ADDRESS_BITS_PER_WORD;
            if (wordsLength <= wordIndex)
                words = Resize(words, wordsLength, wordIndex+1);
            words[wordIndex] &= ~(1 << bitIndex);
        }


    };
}
