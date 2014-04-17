#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cassert>


constexpr bool isInRange(int val, int low, int high) {
     return val >= low && val < high;
}

//compile-time: fails to compile if val outside range
//run-time: throws if val outside range
constexpr bool getValInRange(int val, int low, int high) {
    //The compile-time error can't include the values by language limitation
    //The run-time error can't either due to the compile-time limitation
    return isInRange(val, low, high) ?
        val :
        throw std::logic_error("Value outside range"); //throw can't compile
}

//open interval [low, high)
template<int LOW, int HIGH>
struct StaticRangeInt {
    static_assert(HIGH > LOW, "Value outside range");
    const int _val;
    constexpr StaticRangeInt(int val):_val(getValInRange(val, LOW, HIGH)) {
    }
};


int readVal() {
    std::cout << "Number to put in range? ";
    int val;
    std::cin >> val;
    std::cout << std::endl;
    return val;
}

int main() {
    constexpr auto lo = 3, hi = 6;
    constexpr auto staticVal = 4; //usable at compile-time even w/o constexpr
    //changing staticVal can produce a compile-time error for staticInt
    constexpr StaticRangeInt<lo, hi> staticInt{staticVal};
    const auto dynamicVal = readVal();
    const StaticRangeInt<lo, hi> dynamicInt{dynamicVal}; //may throw

    assert(staticInt._val  == staticVal);
    assert(dynamicInt._val == dynamicVal);
}
