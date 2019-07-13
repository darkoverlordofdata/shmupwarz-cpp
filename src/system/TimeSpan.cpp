#include "system/TimeSpan.h"
/*
 * Replace with thin api wrapper for chrono?
 */
namespace system {

    const TimeSpan TimeSpan::MaxValue = [] { return TimeSpan(INT64_MAX); }(); 
    const TimeSpan TimeSpan::MinValue = [] { return TimeSpan(INT64_MIN); }(); 
    const TimeSpan TimeSpan::Zero = [] { return TimeSpan(0); }(); 

    TimeSpan::TimeSpan(){}
    TimeSpan::TimeSpan(int64_t ticks) {
        mTicks = ticks;
    }
    TimeSpan::~TimeSpan(){}

    int64_t TimeSpan::Ticks() {
        return mTicks;
    }
    int TimeSpan::Days() {
        return (int)((mTicks / TicksPerDay));
    }
    int TimeSpan::Hours() {
        return (int)((mTicks / TicksPerHour) % 24);
    }
    int TimeSpan::Milliseconds() {
        return (int)((mTicks / TicksPerMillisecond) % 1000);
    }
    int TimeSpan::Minutes() {
        return (int)((mTicks / TicksPerMinute) % 60);
    }
    int TimeSpan::Seconds() {
        return (int)((mTicks / TicksPerSecond) % 60);
    }
    double TimeSpan::TotalDays() {
        return ((double)mTicks * DaysPerTick);
    }
    double TimeSpan::TotalHours() {
        return ((double)mTicks * HoursPerTick);
    }
    double TimeSpan::TotalMillisecond() {
        auto temp = (double)mTicks * MillisecondsPerTick;
        if (temp > MaxMilliSeconds)
            return (double)MaxMilliSeconds;

        if (temp < MinMilliSeconds)
            return (double)MinMilliSeconds;

        return temp;

    }
    double TimeSpan::TotalMinutes() {
        return ((double)mTicks * MinutesPerTick);

    }
    double TimeSpan::TotalSeconds() {
        return ((double)mTicks * SecondsPerTick);

    }


    TimeSpan TimeSpan::Add(TimeSpan * ts) {
        int64_t result = mTicks + ts->mTicks;
        // Overflow if signs of operands was identical and result's
        // sign was opposite.
        // >> 63 gives the sign bit (either 64 1's or 64 0's).
        if ((mTicks >> 63 == ts->mTicks >> 63) && (mTicks >> 63 != result >> 63))
            throw exceptions::OverflowException();
        return TimeSpan(result);
     }

    TimeSpan TimeSpan::Sub(TimeSpan * ts) { 
        int64_t result = mTicks - ts->mTicks;
        return TimeSpan(result);
    }

    void TimeSpan::Plus(TimeSpan * ts) { 
        int64_t result = mTicks + ts->mTicks;
        // Overflow if signs of operands was identical and result's
        // sign was opposite.
        // >> 63 gives the sign bit (either 64 1's or 64 0's).
        if ((mTicks >> 63 == ts->mTicks >> 63) && (mTicks >> 63 != result >> 63))
             throw exceptions::OverflowException();
        mTicks = result;
    }

    void TimeSpan::Minus(TimeSpan * ts) { mTicks -= ts->mTicks; }

    TimeSpan TimeSpan::LT(TimeSpan * ts) {  return mTicks < ts->mTicks; }

    TimeSpan TimeSpan::LE(TimeSpan * ts) { return mTicks <= ts->mTicks; }

    TimeSpan TimeSpan::GT(TimeSpan * ts) { return mTicks > ts->mTicks; }

    TimeSpan TimeSpan::GE(TimeSpan * ts) { return mTicks >= ts->mTicks; }

    TimeSpan TimeSpan::NE(TimeSpan * ts) { return mTicks != ts->mTicks; }

    TimeSpan TimeSpan::EQ(TimeSpan * ts) { return mTicks == ts->mTicks; }

    TimeSpan TimeSpan::FromHours(double value) {
        return Interval(value, MillisPerHour);
    }

    TimeSpan TimeSpan::FromMinutes(double value) {
        return Interval(value, MillisPerMinute);
    }

    TimeSpan TimeSpan::FromSeconds(double value) {
        return Interval(value, MillisPerSecond);
    }

    TimeSpan TimeSpan::FromMilliseconds(double value) {
        return Interval(value, 1);
    }

    TimeSpan TimeSpan::FromTicks(int64_t value) {
        return TimeSpan(value);
    }

    TimeSpan TimeSpan::Interval(double value, int scale) {
        // if (Math.isnan(value) != 0)
        //     throw new System.Exception.ArgumentException(System.Environment.GetResourceString("Arg_CannotBeNaN"));
        // Contract.EndContractBlock();
        double tmp = value * scale;
        double millis = tmp + (value >= 0? 0.5: -0.5);
        if ((millis > INT64_MAX / TicksPerMillisecond) || (millis < INT64_MIN / TicksPerMillisecond))
            throw exceptions::OverflowException();
        return TimeSpan((long)millis * TicksPerMillisecond);
    }

    TimeSpan TimeSpan::Duration() {
        if (mTicks==TimeSpan::MinValue.mTicks)
            throw exceptions::OverflowException();
        return TimeSpan(mTicks >= 0? mTicks: -mTicks);
    }

    TimeSpan TimeSpan::Negate() {
        if (mTicks==TimeSpan::MinValue.mTicks)
            throw exceptions::OverflowException();
        return TimeSpan(-mTicks);
    }



}