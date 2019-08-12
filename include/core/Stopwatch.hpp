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
#include <cstdint>
#include <time.h>
#include <sys/time.h>
/**
 * based on .NET Framework: System.Diagnostics.Stopwatch
 */
namespace core {
    static uint64_t GetTimestamp() 
    {
        static struct timeval t{ .tv_sec = 0, .tv_usec = 0 };     
        gettimeofday(&t, nullptr);
        uint64_t ts = t.tv_sec;
        uint64_t us = t.tv_usec;
        return (ts * 1000000LL) + us;
    }

    // static const long TicksPerMillisecond = 10000;
    // static const long TicksPerSecond = TicksPerMillisecond * 1000;

    #define TicksPerMillisecond 10000
    #define TicksPerSecond TicksPerMillisecond * 1000
    // "Frequency" stores the frequency of the high-resolution performance counter, 
    // if one exists. Otherwise it will store TicksPerSecond. 
    // The frequency cannot change while the system is running,
    // so we only need to initialize it once. 
    // static const long Frequency = 1000000L;
    #define Frequency 1000000L
    static bool IsHighResolution = true;
    // performance-counter frequency, in counts per ticks.
    // This can speed up conversion from high frequency performance-counter 
    // to ticks. 
    static const double TickFrequency = (double)TicksPerSecond / (double)Frequency;

    class Stopwatch {
        private:
        long mElapsed;
        uint64_t mStartTimeStamp;
        bool mIsRunning;

        public:
        void Reset() {
            mElapsed = 0;
            mIsRunning = false;
            mStartTimeStamp = 0;
        }

        Stopwatch(){
            Reset();
        }
        ~Stopwatch(){}

        void Start() {
            // Calling start on a running Stopwatch is a no-op.
            if(!mIsRunning) {
                mStartTimeStamp = GetTimestamp();                 
                mIsRunning = true;
            }
        }
     
        private:
        long GetRawElapsedTicks() {
            long timeElapsed = mElapsed;
 
            if( mIsRunning) {
                // If the StopWatch is running, add elapsed time since
                // the Stopwatch is started last time. 
                uint64_t currentTimeStamp = GetTimestamp();    
                uint64_t elapsedUntilNow = currentTimeStamp - mStartTimeStamp;
                timeElapsed = (long)elapsedUntilNow;
            }
            return timeElapsed;
        }   
 
        // Get the elapsed ticks.        
        long GetElapsedDateTimeTicks() {
            auto rawTicks = GetRawElapsedTicks();
            if( IsHighResolution) {
                // convert high resolution perf counter to DateTime ticks
                auto dticks = rawTicks;
                dticks *= TickFrequency;
                return (long)dticks;                        
            }
            else {
                return rawTicks;
            }
        }   


        public:
 
        static Stopwatch* StartNew() {
            auto stopwatch = new Stopwatch();
            stopwatch->Start();
            return stopwatch;
        }
        void Stop() {
            // Calling stop on a stopped Stopwatch is a no-op.
            if( mIsRunning) {
                auto endTimeStamp = GetTimestamp();                 
                auto elapsedThisPeriod = endTimeStamp - mStartTimeStamp;
                mElapsed += (long)elapsedThisPeriod;
                mIsRunning = false;
 
                if (mElapsed < 0) {
                    // When measuring small time periods the StopWatch.Elapsed* 
                    // properties can return negative values.  This is due to 
                    // bugs in the basic input/output system (BIOS) or the hardware
                    // abstraction layer (HAL) on machines with variable-speed CPUs
                    // (e.g. Intel SpeedStep).
 
                    mElapsed = 0;
                }
            }
        }
 
        // Convenience method for replacing {sw.Reset(); sw.Start();} with a single sw.Restart()
        void Restart() {
            mElapsed = 0;
            mStartTimeStamp = GetTimestamp();
            mIsRunning = true;
        }
 
        bool IsRunning() { 
            return mIsRunning; 
        }
 
        TimeSpan* Elapsed() {
            return new TimeSpan( GetElapsedDateTimeTicks());
        }
        
        
        long ElapsedMilliseconds() { 
            return GetElapsedDateTimeTicks()/TicksPerMillisecond; 
        }  
        
        long ElapsedTicks() { 
            return GetRawElapsedTicks();
        }
    };
}