// Tests for the solutions in "Greeks For Greeks/Array".
//
// Every solution is a stand-alone .cpp file (some have their own demo main()),
// so each one is included here unchanged inside its own namespace, with its
// main() renamed. Nothing in the solution files has to change to be tested.
//
// Run from the repository root:
//   g++ -std=c++17 tests/array_tests.cpp -o tests/array_tests.out && ./tests/array_tests.out
//
// Two solutions include <bits/stdc++.h>, which only GCC ships (g++-15 on
// macOS). With another compiler those two are skipped and the rest still run.

#if __has_include(<bits/stdc++.h>)
#include <bits/stdc++.h>
#define HAVE_BITS_STDCPP 1
#else
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
#endif

#define main solutionDemoMain

namespace arrayReverse {
#include "../Greeks For Greeks/Array/Array Revers.cpp"
}
namespace boyerMoore {
#include "../Greeks For Greeks/Array/Boyer-MooreVoting Algorithm.cpp"
}
namespace kadane {
#include "../Greeks For Greeks/Array/Kadane's Algorithm.cpp"
}
namespace minimizeHeights {
#include "../Greeks For Greeks/Array/Minimize the maximum difference between the heights.cpp"
}
namespace moveZeros {
#include "../Greeks For Greeks/Array/Move All Zeros to End of Array.cpp"
}
namespace missingPositive {
#include "../Greeks For Greeks/Array/smallest missing possitive number.cpp"
}
namespace stockManyTransactions {
#include "../Greeks For Greeks/Array/Stock Buy and Sell.cpp"
}
namespace stockOneTransaction {
#include "../Greeks For Greeks/Array/Stock by and Sell max on transaction.cpp"
}
#ifdef HAVE_BITS_STDCPP
namespace rotateArray {
#include "../Greeks For Greeks/Array/Rotate An array.cpp"
}
namespace secondLargest {
#include "../Greeks For Greeks/Array/Second Largest.cpp"
}
#endif

#undef main

typedef std::vector<int> V;

static int checks = 0;
static int failures = 0;

#define CHECK(cond)                                                          \
    do {                                                                     \
        checks++;                                                            \
        if (!(cond)) {                                                       \
            failures++;                                                      \
            std::cerr << "FAIL line " << __LINE__ << ": " << #cond << "\n"; \
        }                                                                    \
    } while (0)

static void testArrayReverse() {
    V arr = {1, 4, 3, 2, 6, 5};
    arrayReverse::reverseArray(arr);
    CHECK(arr == (V{5, 6, 2, 3, 4, 1}));

    V odd = {4, 5, 1};
    arrayReverse::reverseArray(odd);
    CHECK(odd == (V{1, 5, 4}));

    V one = {7};
    arrayReverse::reverseArray(one);
    CHECK(one == (V{7}));

    V empty;
    arrayReverse::reverseArray(empty);
    CHECK(empty.empty());
}

static void testBoyerMooreVoting() {
    V twoWinners = {2, 2, 3, 1, 3, 2, 1, 1};
    CHECK(boyerMoore::findMajority(twoWinners) == (V{1, 2}));

    V oneWinner = {-5, 3, -5};
    CHECK(boyerMoore::findMajority(oneWinner) == (V{-5}));

    // 2 and 4 appear exactly n/3 times, which is not "more than n/3"
    V noWinner = {3, 2, 2, 4, 1, 4};
    CHECK(boyerMoore::findMajority(noWinner).empty());

    // already in increasing order, nothing to swap
    V sortedWinners = {1, 1, 2, 2};
    CHECK(boyerMoore::findMajority(sortedWinners) == (V{1, 2}));

    // -1 is the initial value of both candidates; it must still be counted
    // correctly and reported only once
    V minusOnes = {-1, -1, 2};
    CHECK(boyerMoore::findMajority(minusOnes) == (V{-1}));
    V onlyMinusOnes = {-1, -1, -1};
    CHECK(boyerMoore::findMajority(onlyMinusOnes) == (V{-1}));

    V allSame = {6, 6, 6, 6};
    CHECK(boyerMoore::findMajority(allSame) == (V{6}));

    V empty;
    CHECK(boyerMoore::findMajority(empty).empty());
}

static void testKadane() {
    V mixed = {2, 3, -8, 7, -1, 2, 3};
    CHECK(kadane::maxSubarraySum(mixed) == 11);

    V allNegative = {-2, -4};
    CHECK(kadane::maxSubarraySum(allNegative) == -2);

    V allPositive = {5, 4, 1, 7, 8};
    CHECK(kadane::maxSubarraySum(allPositive) == 25);

    V one = {-7};
    CHECK(kadane::maxSubarraySum(one) == -7);
}

static void testMinimizeHeights() {
    V a = {1, 5, 8, 10};
    CHECK(minimizeHeights::getMinDiff(a, 2) == 5);

    V b = {3, 9, 12, 16, 20};
    CHECK(minimizeHeights::getMinDiff(b, 3) == 11);

    // the function sorts its argument before working on it
    V unsorted = {10, 1, 8, 5};
    CHECK(minimizeHeights::getMinDiff(unsorted, 2) == 5);
    CHECK(unsorted == (V{1, 5, 8, 10}));

    // k is larger than every height, so no tower can be lowered
    V low = {1, 2, 3};
    CHECK(minimizeHeights::getMinDiff(low, 5) == 2);

    V one = {4};
    CHECK(minimizeHeights::getMinDiff(one, 3) == 0);
}

static void testMoveZeros() {
    V arr = {1, 2, 0, 4, 3, 0, 5, 0};
    moveZeros::pushZerosToEnd(arr);
    CHECK(arr == (V{1, 2, 4, 3, 5, 0, 0, 0}));

    V noZeros = {10, 20, 30};
    moveZeros::pushZerosToEnd(noZeros);
    CHECK(noZeros == (V{10, 20, 30}));

    V onlyZeros = {0, 0};
    moveZeros::pushZerosToEnd(onlyZeros);
    CHECK(onlyZeros == (V{0, 0}));

    V empty;
    moveZeros::pushZerosToEnd(empty);
    CHECK(empty.empty());
}

static void testSmallestMissingPositive() {
    V a = {2, -3, 4, 1, 1, 7};
    CHECK(missingPositive::missingNumber(a) == 3);

    V b = {5, 3, 2, 5, 1};
    CHECK(missingPositive::missingNumber(b) == 4);

    V noPositives = {-8, 0, -1, -4, -3};
    CHECK(missingPositive::missingNumber(noPositives) == 1);

    V complete = {3, 1, 2};
    CHECK(missingPositive::missingNumber(complete) == 4);

    V empty;
    CHECK(missingPositive::missingNumber(empty) == 1);
}

static void testStockManyTransactions() {
    CHECK(stockManyTransactions::maxProfit(V{100, 180, 260, 310, 40, 535, 695}) == 865);
    CHECK(stockManyTransactions::maxProfit(V{4, 2, 2, 2, 4}) == 2);
    CHECK(stockManyTransactions::maxProfit(V{9, 7, 4, 1}) == 0);
    CHECK(stockManyTransactions::maxProfit(V{5}) == 0);
    CHECK(stockManyTransactions::maxProfit(V{}) == 0);
}

static void testStockOneTransaction() {
    V a = {7, 10, 1, 3, 6, 9, 2};
    CHECK(stockOneTransaction::maxProfit(a) == 8);

    V falling = {7, 6, 4, 3, 1};
    CHECK(stockOneTransaction::maxProfit(falling) == 0);

    V rising = {1, 3, 6, 9, 11};
    CHECK(stockOneTransaction::maxProfit(rising) == 10);

    V one = {5};
    CHECK(stockOneTransaction::maxProfit(one) == 0);
}

#ifdef HAVE_BITS_STDCPP
static void testRotateArray() {
    V arr = {1, 2, 3, 4, 5, 6};
    rotateArray::rotateArr(arr, 2);
    CHECK(arr == (V{3, 4, 5, 6, 1, 2}));

    // d larger than the size wraps around
    V wrap = {1, 2, 3};
    rotateArray::rotateArr(wrap, 4);
    CHECK(wrap == (V{2, 3, 1}));

    V zero = {1, 2, 3};
    rotateArray::rotateArr(zero, 0);
    CHECK(zero == (V{1, 2, 3}));

    V full = {1, 2, 3};
    rotateArray::rotateArr(full, 3);
    CHECK(full == (V{1, 2, 3}));
}

static void testSecondLargest() {
    V a = {12, 35, 1, 10, 34, 1};
    CHECK(secondLargest::getSecondLargest(a) == 34);

    V b = {10, 5, 10};
    CHECK(secondLargest::getSecondLargest(b) == 5);

    V allSame = {10, 10, 10};
    CHECK(secondLargest::getSecondLargest(allSame) == -1);

    V one = {8};
    CHECK(secondLargest::getSecondLargest(one) == -1);
}
#endif

int main() {
    testArrayReverse();
    testBoyerMooreVoting();
    testKadane();
    testMinimizeHeights();
    testMoveZeros();
    testSmallestMissingPositive();
    testStockManyTransactions();
    testStockOneTransaction();
#ifdef HAVE_BITS_STDCPP
    testRotateArray();
    testSecondLargest();
#else
    std::cout << "skipped: Rotate An array, Second Largest (need <bits/stdc++.h>)\n";
#endif

    std::cout << (checks - failures) << "/" << checks << " checks passed\n";
    return failures == 0 ? 0 : 1;
}
