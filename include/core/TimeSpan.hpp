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

/**
 * based on .NET Framework: System.TimeSpan
 */
namespace core {

        #define TicksPerMillisecond  10000.0
        #define TicksPerSecond TicksPerMillisecond * 1000.0   // 10,000,000
        #define TicksPerMinute TicksPerSecond * 60.0         // 600,000,000
        #define TicksPerHour TicksPerMinute * 60.0        // 36,000,000,000
        #define TicksPerDay TicksPerHour * 24.0          // 864,000,000,000

        #define MillisecondsPerTick 1.0 / (TicksPerMillisecond)
        #define SecondsPerTick  1.0 / (TicksPerSecond)         // 0.0001
        #define MinutesPerTick 1.0 / (TicksPerMinute) // 1.6666666666667e-9
        #define HoursPerTick 1.0 / (TicksPerHour) // 2.77777777777777778e-11
        #define DaysPerTick 1.0 / (TicksPerDay) // 1.1574074074074074074e-12
        #define MillisPerSecond 1000.0
        #define MillisPerMinute (MillisPerSecond) * 60.0 //     60,000
        #define MillisPerHour (MillisPerMinute) * 60.0   //  3,600,000
        #define MillisPerDay (MillisPerHour) * 24.0      // 86,400,000

        #define MaxSeconds INT64_MAX / (TicksPerSecond)
        #define MinSeconds INT64_MIN / (TicksPerSecond)
        #define MaxMilliSeconds INT64_MAX / TicksPerMillisecond
        #define MinMilliSeconds INT64_MIN / TicksPerMillisecond
        #define TicksPerTenthSecond (TicksPerMillisecond * 100)

    class TimeSpan {
        public:
        int64_t mTicks = 0;

        static const TimeSpan MaxValue; // = new TimeSpan(INT64_MAX);
        static const TimeSpan MinValue; // = new TimeSpan(INT64_MIN);
        static const TimeSpan Zero;     // = new TimeSpan(0);

        // static TimeSpan MaxValue;

        TimeSpan(){}
        TimeSpan(int64_t ticks) {
            mTicks = ticks;
        }
        ~TimeSpan(){}

        int64_t Ticks() {
            return mTicks;
        }
        int Days() {
            return (int)((mTicks / TicksPerDay));
        }
        int Hours() {
            return (int)((mTicks / TicksPerHour)) % 24;
        }
        int Milliseconds() {
            return (int)((mTicks / TicksPerMillisecond)) % 1000;
        }
        int Minutes() {
            return (int)((mTicks / TicksPerMinute)) % 60;
        }
        int Seconds() {
            return (int)((mTicks / TicksPerSecond)) % 60;
        }
        double TotalDays() {
            return ((double)mTicks * DaysPerTick);
        }
        double TotalHours() {
            return ((double)mTicks * HoursPerTick);
        }
        double TotalMilliseconds() {
            auto temp = (double)mTicks * MillisecondsPerTick;
            if (temp > MaxMilliSeconds)
                return (double)MaxMilliSeconds;

            if (temp < MinMilliSeconds)
                return (double)MinMilliSeconds;

            return temp;

        }
        double TotalMinutes() {
            return ((double)mTicks * MinutesPerTick);

        }
        double TotalSeconds() {
            return ((double)mTicks * SecondsPerTick);

        }


        TimeSpan& operator +=(const TimeSpan& rhs) {
            mTicks += rhs.mTicks;
            return *this;
        }

        TimeSpan& operator -=(const TimeSpan& rhs) {
            mTicks -= rhs.mTicks;
            return *this;
        }

        TimeSpan operator+(TimeSpan  ts) {
            int64_t result = mTicks + ts.mTicks;
            // Overflow if signs of operands was identical and result's
            // sign was opposite.
            // >> 63 gives the sign bit (either 64 1's or 64 0's).
            if ((mTicks >> 63 == ts.mTicks >> 63) && (mTicks >> 63 != result >> 63))
                throw exceptions::OverflowException();
            return TimeSpan(result);
        }

        TimeSpan operator-(TimeSpan  ts) { 
            int64_t result = mTicks - ts.mTicks;
            return TimeSpan(result);
        }

        // void Minus(TimeSpan ts) { mTicks -= ts.mTicks; }

        bool operator<(TimeSpan ts) {  return mTicks < ts.mTicks; }

        bool operator<=(TimeSpan ts) { return mTicks <= ts.mTicks; }

        bool operator>(TimeSpan ts) { return mTicks > ts.mTicks; }

        bool operator>=(TimeSpan ts) { return mTicks >= ts.mTicks; }

        bool operator!=(TimeSpan ts) { return mTicks != ts.mTicks; }

        bool operator==(TimeSpan ts) { return mTicks == ts.mTicks; }

        static TimeSpan FromHours(double value) {
            return Interval(value, MillisPerHour);
        }

        static TimeSpan FromMinutes(double value) {
            return Interval(value, MillisPerMinute);
        }

        static TimeSpan FromSeconds(double value) {
            return Interval(value, MillisPerSecond);
        }

        static TimeSpan FromMilliseconds(double value) {
            return Interval(value, 1);
        }

        static TimeSpan FromTicks(int64_t value) {
            TimeSpan retval = TimeSpan(value);
            return retval;
            // return TimeSpan(value);
        }

        static TimeSpan Interval(double value, int scale) {
            double tmp = value * scale;
            double millis = tmp + (value >= 0? 0.5: -0.5);
            if ((millis > INT64_MAX / TicksPerMillisecond) || (millis < INT64_MIN / TicksPerMillisecond))
                throw exceptions::OverflowException();
            return TimeSpan((long)millis * TicksPerMillisecond);
        }

        TimeSpan Duration() {
            if (mTicks==MinValue.mTicks)
                throw exceptions::OverflowException();
            return TimeSpan(mTicks >= 0? mTicks: -mTicks);
        }

        TimeSpan Negate() {
            if (mTicks==MinValue.mTicks)
                throw exceptions::OverflowException();
            return TimeSpan(-mTicks);
        }
    };

    inline const TimeSpan TimeSpan::MaxValue = TimeSpan(INT64_MAX);
    inline const TimeSpan TimeSpan::MinValue = TimeSpan(INT64_MIN);
    inline const TimeSpan TimeSpan::Zero = TimeSpan(0);
    
}
