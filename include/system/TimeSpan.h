#pragma once
#include <cstdint>
#include "system/Exceptions.h"

namespace system {
    class TimeSpan {
    public:
        TimeSpan();
        TimeSpan(int64_t ticks);
        ~TimeSpan();

        const int64_t TicksPerMillisecond =  10000;
        const int64_t TicksPerSecond = TicksPerMillisecond * 1000;   // 10,000,000
        const int64_t TicksPerMinute = TicksPerSecond * 60;         // 600,000,000
        const int64_t TicksPerHour = TicksPerMinute * 60;        // 36,000,000,000
        const int64_t TicksPerDay = TicksPerHour * 24;          // 864,000,000,000
        static const TimeSpan MaxValue; // = new TimeSpan(INT64_MAX);
        static const TimeSpan MinValue; // = new TimeSpan(INT64_MIN);
        static const TimeSpan Zero; // = new TimeSpan(0);
        const int64_t MaxSeconds = INT64_MAX / TicksPerSecond;
        const int64_t MinSeconds = INT64_MIN / TicksPerSecond;
        const int64_t MaxMilliSeconds = INT64_MAX / TicksPerMillisecond;
        const int64_t MinMilliSeconds = INT64_MIN / TicksPerMillisecond;
        const int64_t TicksPerTenthSecond = TicksPerMillisecond * 100;
 
        int64_t mTicks = 0;

        int64_t Ticks();
        int Days();
        int Hours();
        int Milliseconds();
        int Minutes();
        int Seconds();
        double TotalDays();
        double TotalHours();
        double TotalMillisecond();
        double TotalMinutes();
        double TotalSeconds();
        TimeSpan Add(TimeSpan * ts);
        TimeSpan Sub(TimeSpan * ts);
        void Plus(TimeSpan * ts);
        void Minus(TimeSpan * ts);
        TimeSpan LT(TimeSpan * ts);
        TimeSpan LE(TimeSpan * ts);
        TimeSpan GT(TimeSpan * ts);
        TimeSpan GE(TimeSpan * ts);
        TimeSpan NE(TimeSpan * ts);
        TimeSpan EQ(TimeSpan * ts);
        TimeSpan FromHours(double value);
        TimeSpan FromMinutes(double value);
        TimeSpan FromSeconds(double value);
        TimeSpan FromMilliseconds(double value);
        TimeSpan FromTicks(int64_t value);
        TimeSpan Interval(double value, int scale);
        TimeSpan Duration();
        TimeSpan Negate();

    private:
        const double MillisecondsPerTick = 1.0 / TicksPerMillisecond;
        const double SecondsPerTick =  1.0 / TicksPerSecond;         // 0.0001
        const double MinutesPerTick = 1.0 / TicksPerMinute; // 1.6666666666667e-9
        const double HoursPerTick = 1.0 / TicksPerHour; // 2.77777777777777778e-11
        const double DaysPerTick = 1.0 / TicksPerDay; // 1.1574074074074074074e-12
        const int MillisPerSecond = 1000;
        const int MillisPerMinute = MillisPerSecond * 60; //     60,000
        const int MillisPerHour = MillisPerMinute * 60;   //  3,600,000
        const int MillisPerDay = MillisPerHour * 24;      // 86,400,000
 

    };
}
