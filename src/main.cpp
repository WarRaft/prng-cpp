#include <iostream>
#include <bit>
#include <vector>
#include <cmath>
#include "prng.hpp"

using namespace std;

void test() {
    // Test for seed 100500, [0, 1000]
    PRNG prng(100500);
    prng.rng(); // skip first
    vector<int> expected_int_0_1000 = {691, 571, 655, 56, 547, 17, 431, 811, 707, 355, 723};
    bool pass_int = true;
    for (int i = 0; i <= 10; i++) {
        int val = prng.rand(0, 1000);
        if (val != expected_int_0_1000[i]) {
            cout << "Mismatch at i=" << i << " expected " << expected_int_0_1000[i] << " got " << val << endl;
            pass_int = false;
        }
    }
    if (pass_int) cout << "Test [0,1000] PASSED" << endl;
    else cout << "Test [0,1000] FAILED" << endl;

    // Test for seed 100500, [-1000, 0]
    prng.seed(100500);
    prng.rng(); // skip first
    vector<int> expected_int_neg1000_0 = {-309, -429, -345, -944, -453, -983, -569, -189, -293, -645, -277};
    bool pass_int_neg = true;
    for (int i = 0; i <= 10; i++) {
        int val = prng.rand(-1000, 0);
        if (val != expected_int_neg1000_0[i]) {
            cout << "Mismatch at i=" << i << " expected " << expected_int_neg1000_0[i] << " got " << val << endl;
            pass_int_neg = false;
        }
    }
    if (pass_int_neg) cout << "Test [-1000,0] PASSED" << endl;
    else cout << "Test [-1000,0] FAILED" << endl;

    // Test for seed 100500, [0.f, 1000.f]
    prng.seed(100500);
    prng.rng(); // skip first
    vector<float> expected_float_0_1000 = {739.494f, 201.548f, 203.158f, 101.963f, 864.071f, 924.319f, 788.981f, 189.968f, 984.311f, 693.438f, 881.644f};
    bool pass_float = true;
    for (int i = 0; i <= 10; i++) {
        float val = prng.rand(0.f, 1000.f);
        if (abs(val - expected_float_0_1000[i]) > 0.001f) {
            cout << "Mismatch at i=" << i << " expected " << expected_float_0_1000[i] << " got " << val << endl;
            pass_float = false;
        }
    }
    if (pass_float) cout << "Test [0.f,1000.f] PASSED" << endl;
    else cout << "Test [0.f,1000.f] FAILED" << endl;

    // Test for seed 100500, [-1000.f, 0.f]
    prng.seed(100500);
    prng.rng(); // skip first
    vector<float> expected_float_neg1000_0 = {-260.506f}; // only first in GEN.md
    bool pass_float_neg = true;
    for (int i = 0; i < 1; i++) { // only check first
        float val = prng.rand(-1000.f, 0.f);
        if (abs(val - expected_float_neg1000_0[i]) > 0.001f) {
            cout << "Mismatch at i=" << i << " expected " << expected_float_neg1000_0[i] << " got " << val << endl;
            pass_float_neg = false;
        }
    }
    if (pass_float_neg) cout << "Test [-1000.f,0.f] PASSED" << endl;
    else cout << "Test [-1000.f,0.f] FAILED" << endl;
}

int main() {
    test();
    return 0;
}
