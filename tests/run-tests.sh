#!/usr/bin/env sh
set -e

#Should work for any compiler
compiler=clang++
#C++17 is required for this library
standard=c++17
flags="-std=$standard -pedantic-errors -I.."

echo "RUNNING TEST ORACLE (baseline for real tests; doesn't use strong_types)"
$compiler $flags -o test-oracle test-oracle.cpp
echo "NOTE: There should be some warnings; these are expected."
echo "  Output of test oracle (should be 435):"
./test-oracle
echo

echo "RUNNING TESTS (uses strong_types.hpp)"
$compiler $flags -o test test.cpp
echo "  Output of test (if tests passed, will be 435; else, some test(s) failed):"
./test

echo "Cleaning up..."
rm test-oracle
rm test
