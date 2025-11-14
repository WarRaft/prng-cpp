#include <iostream>

template<class T>
T __ROL__(T value, int count) {
    const unsigned int nbits = sizeof(T) * 8;

    if (count > 0) {
        count %= nbits;
        T high = value >> (nbits - count);
        if (T(-1) < 0) // signed value
            high &= ~((T(-1) << count));
        value <<= count;
        value |= high;
    } else {
        count = -count % nbits;
        T low = value << (nbits - count);
        value >>= count;
        value |= low;
    }
    return value;
}

using namespace std;

constexpr unsigned int gnoise32_[64] = {
    2569475214u, 147303165u, 524216021u, 3663051766u, 1783275637u, 4288134632u, 2679938014u, 1184991873u, 1675823982u,
    1567390326u, 3395933064u, 632899523u, 1067625347u, 3128705446u, 26586341u, 3238645630u, 1903190745u, 33938317u,
    1424983844u, 808965318u, 2076908496u, 3973637304u, 3702378057u, 3298076947u, 229521807u, 249385496u, 2247490168u,
    1840239192u, 995340964u, 3192956241u, 301215228u, 4044789832u, 1715330950u, 791561310u, 392890166u, 3058444683u,
    3881798114u, 3777079245u, 3982870861u, 597487358u, 79134003u, 1076533918u, 4082831539u, 2451339138u, 1461603872u,
    2349232674u, 4218629223u, 3205153369u, 217668729u, 1746016808u, 1108948084u, 4169449649u, 2635460664u, 1866134112u,
    2448134324u, 1630895901u, 1443050074u, 2469119395u, 1128992640u, 1021356279u, 644141462u, 1338787287u, 3051991240u,
    3929134592u
};

class PRNG {
public:
    explicit PRNG(const unsigned int seed) {
        this->seed(seed);
    }

    void seed(const unsigned int seed) {
        this->rndacc = seed;
        this->rndvls = (seed + 17 * (seed / 0x2F)) << 26 | (seed % 0x35) << 18 | 4 * (seed % 0x3D) | (seed % 0x3B) <<
                       10;
    }

    unsigned int rndacc{};
    unsigned int rndvls{};

    long long rng() {
        unsigned int rndvl = this->rndvls;
        int v2 = 184;
        int v3 = 200;
        int v4 = 212;
        if (((unsigned char *) &rndvl)[3] >= 0x4) v2 = -4;

        const signed int v5 = ((unsigned char *) &rndvl)[3] + v2;
        if ((rndvl & 0xFF0000) >= 0xC0000) v3 = -12;
        const int v6 = ((unsigned char *) &rndvl)[2] + v3;
        if (((unsigned char *) &rndvl)[1] >= 0x18u) v4 = -24;
        const int v7 = ((unsigned char *) &rndvl)[1] + v4;
        int v8 = 216;
        if (static_cast<unsigned char>(rndvl) >= 0x1Cu) v8 = -28;
        const int v9 = static_cast<unsigned char>(rndvl) + v8;
        const unsigned int v10 = this->rndacc
                                 + (
                                     (*reinterpret_cast<const unsigned int *>((char *) gnoise32_ + v9))
                                     ^ __ROL__(
                                         (unsigned int) *reinterpret_cast<const unsigned int *>(
                                             (char *) gnoise32_ + v7), 3)
                                     ^ __ROL__(
                                         (unsigned int) *reinterpret_cast<const unsigned int *>(
                                             (char *) gnoise32_ + v6), 2)
                                     ^ __ROL__(
                                         (unsigned int) *reinterpret_cast<const unsigned int *>(
                                             (char *) gnoise32_ + v5), 1)
                                 );
        this->rndvls = v9 | (v7 | (v6 | v5 << 8) << 8) << 8;
        const long long result = v10;
        this->rndacc = v10;
        return result;
    }

    int rand(const int lowBound, const int highBound) {
        if (lowBound == highBound) return lowBound;
        const unsigned int v5 = rng();
        int v6 = lowBound - highBound;
        if (static_cast<int>(lowBound) <= highBound) v6 = highBound - lowBound;
        return static_cast<int>(
            lowBound + (static_cast<unsigned int>(v6 + 1) * static_cast<unsigned long long>(v5) >>
                        32));
    }


    float rand(const float a1, const float a2) {
        if (0x3456BF95u > (static_cast<unsigned int>(a1 - a2) & 0x7FFFFFFF)) return a1;

        int e9 = static_cast<int>(rng()) & 0x7FFFFF | 0x3F800000;

        const float d1 = *reinterpret_cast<float *>(&e9);
        unsigned int v13 = 0xBF800000;
        const float d2 = *reinterpret_cast<float *>(&v13);

        const float v3 = a1 > a2 ? a1 - a2 : a2 - a1;
        return a1 + v3 * (d1 + d2);
    }
};

class Data {
public:
    explicit Data(
        const unsigned int seed,
        const int mini,
        const int maxi,
        const float minf,
        const float maxf
    ) {
        this->seed = seed;
        this->mini = mini;
        this->maxi = maxi;
        this->minf = minf;
        this->maxf = maxf;
    }

    unsigned int seed;
    int mini;
    int maxi;
    float minf;
    float maxf;
};


int main() {
    std::cout << "\n\nSet seed 100500, [-1000.0, 0.0]\n";
    PRNG prng(100500);
    //prng.rng();
    for (int i = 0; i <= 10; i++) {
        std::cout << "i = " << i << " | " << prng.rand(-1000.f, 0.f) << std::endl;
    }


    if (true) {
        std::cout << "\n\nSet seed 100500, [0, 1000]\n";
        prng.seed(100500);
        for (int i = 0; i <= 10; i++) {
            std::cout << "i = " << i << " | " << prng.rand(0, 1000) << std::endl;
        }

        std::cout << "\n\nSet seed 100500, [-1000, 0]\n";
        prng.seed(100500);
        for (int i = 0; i <= 10; i++) {
            std::cout << "i = " << i << " | " << prng.rand(-1000, 0) << std::endl;
        }
    }

    return 0;
}
