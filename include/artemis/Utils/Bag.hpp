/* ******************************************************************************
 * Copyright 2019 darkoverlordofdata.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
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
    class Bag : public ImmutableBag<E> {
        
    private:
        int mCount;
        int mSize;
        E *mData;

    public:
        Bag() {
            Init(20);
        };
        
        
        Bag(int capacity) {
            Init(capacity);
        };
        
        /**
         *    If set is used, the bag might
         *    contain gaps between indexes. Use this to get a
         *    complete bag. No changes will be made to the original bag.
         */
        Bag<E> * GetGapless(){
            
            Bag<E> * bag = new Bag<E>(mCount);
            //int c = 0;
            
            for(int i=0; i < mSize; i++)
            {
                if(mData[i] != nullptr){
                    bag->Add(mData[i]);
                }
            }
            
            return bag;
            
        }
        
        /**
         * Adds an object to the bag.
         * Mixing add and set is not encouraged.
         * Note: set can create gaps between indexes where
         * the object mCount is irrelevant to the order.
         *
         * Autmatically grows the bag if necessary.
         *
         * @param o The object to be added.
         **/
        void Add(E o) {
            if(mSize == mCount)Grow();
            
            mData[mCount++] = o;
        };
        
        void AddAll(Bag<E> & bag) {
            
            for(int i=0; i < bag.mSize ; i++) {
                Add(bag.mData[i]);
            }
        };
        
        /**
         * Sets every pointer to NULLs. Does not delete mData.
         */
        void Clear() {
            for(int i=0; i<mSize; i++) {
                mData[i] = nullptr;
            }
            
            mCount = 0;
            
        };
        
        bool Contains(E o) {
            
            for(int i=0; i<mCount; i++)
                if(o == mData[i])
                    return true;
            
            return false;
        };
        
        virtual E Get(int index) {
            if (index >= mSize) return nullptr;
            return (E)mData[index];
        };
        
        virtual int GetCapacity() {return mSize;};
        virtual bool IsEmpty() {return mCount == 0;};
        /**
         * Returns the amount of objects in the bag.
         *
         **/
        virtual int GetCount() {return mCount;};
        
        bool remove(E o) {
            
            for(int i=0; i<mCount; i++) {
                if(o == mData[i]) {
                    Remove(i);
                    return true;
                }
            }
            
            return false;
        };
        
        E Remove(int index) {
            if(mCount == 0) return nullptr;
            
            E object = mData[index];
            mData[index] = mData[mCount-1];
            mData[mCount-1] = nullptr;
            mCount--;
            return (E) object;
        };
        
        bool RemoveAll(Bag<E> bag) {
            bool mod = false;
            
            for(int i=0; i<bag.mCount; i++)
                for(int j= 0; j< mCount ; j++)
                    if(bag.mData[i] == mData[j]) {
                        Remove(j);
                        j--; // ?
                        mod = true;
                        break;
                    }
            
            return mod;
            
        };
        
        
        E RemoveLast() {
            if(!IsEmpty()) {
                E object = mData[mCount-1];
                mData[mCount-1] = nullptr;
                --mCount;
                return (E) object;
            }
            
            return nullptr;
        };
        
        
        bool Set(int index, E o) {
            
            if(index >= mSize) Grow(index*2);
            
            
            if(o == nullptr && mData[index] != nullptr){
                mCount--;
            }
            else if(o != nullptr && mData[index] == nullptr){
                mCount++;
            };
            
            mData[index] = o;
            return true;
        };
        
        
        void operator += (Bag<E> &bag) {
            AddAll(bag);
        };
        
        
        void DeleteData(){
            
            for(int i=0; i<mSize; i++)
            {
                delete mData[i];
                mData[i] = nullptr;
            }
            mCount = 0;
        }
        
        virtual ~Bag<E>() {
            delete[] mData;
        };
        
        
    private:
        void Grow() {
            int newCapacity =(mSize * 3.0f) * 0.5f + 1.0f;
            Grow(newCapacity);
        };
        
        void Grow(int newCapacity) {
            E* newData = new E[newCapacity];
            
            for (int i = 0; i < mSize; i++)
                newData[i] = mData[i];
            for (int i = mSize; i < newCapacity; i++)
                newData[i] = nullptr;

            delete[] mData;

            mSize = newCapacity;
            mData = newData;
        };
        
        void Init(int capacity) {
            mSize = capacity;
            mCount = 0;
            mData = new E[capacity];
            Clear();
        }
        
    };
}