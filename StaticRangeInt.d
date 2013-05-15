#!/usr/bin/rdmd
import std.stdio;
import std.exception;
import std.conv;


auto isInRange(int val, int low, int high) {
    return val >= low && val < high;
}

//open interval [low, high)
struct StaticRangeInt(int LOW, int HIGH) if(HIGH > LOW) {
    immutable int _val;
    this(int val) {
        enforce(isInRange(val, LOW, HIGH),
                "Value must be in [" ~ to!string(LOW) ~ ", " ~ to!string(HIGH) ~ ")");
        _val = val;
    }
}

auto readVal() {
    write("Number to put in range? ");
    int val;
    readf(" %d", &val);
    writeln();
    return val;
}

void main() {
    immutable lo = 3, hi = 6;
    immutable staticVal = 4;
    //changing staticVal can produce a compile-time error for staticInt
    static immutable staticInt = StaticRangeInt!(lo, hi)(staticVal);
    immutable dynamicVal = readVal();
    immutable dynamicInt = StaticRangeInt!(lo, hi)(dynamicVal);
    
    assert(staticInt._val  == staticVal);
    assert(dynamicInt._val == dynamicVal);
}
