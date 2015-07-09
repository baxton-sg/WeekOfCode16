

#include <iostream>
#include <cmath>


using namespace std;

typedef unsigned long long ULONG;

const ULONG MASK = 1000000000 + 7;




void add(int num, int num_zeros, ULONG& sum) {
    if (num_zeros <= 8) {
        sum += num * pow(10, num_zeros);
cout << (num * pow(10, num_zeros)) << endl;
    }
    else {
        int mul = num_zeros / 8; // 8 <= 100M
        int deg = num_zeros - mul * 8;
        int val = num * pow(10, deg) * mul * 999307;

        sum += val;
    }
    sum = sum % MASK;
}


ULONG fact(ULONG n) {
    ULONG res = 1;
    while (n) 
        res *= n--;
    return res;
}

void solve_partially(int x, int y, int z, ULONG& sum) {

    if (0 == (x + y + z))
        return;

cout << x << " " << y << " " << z << endl;

    int deg = x + y + z - 1;
    int cod = x + y + z;

    int comb = fact(cod);
    if (x > 1)
        comb /= fact(x);
    if (y > 1)
        comb /= fact(y);
    if (z > 1)
        comb /= fact(z);
    

    if (x) {
        int rep = comb >= cod ? comb / cod * x : comb;
        int tmp_deg = deg;
        while (rep--) {
            while(tmp_deg >= 0) {
                add(4, tmp_deg, sum);
                --tmp_deg;
            }
            sum = sum % MASK;
            tmp_deg = deg;
cout << "sum: " << sum << endl;
        }
    }

    if (y) {
        int rep = comb >= cod ? comb / cod * y : comb;
        int tmp_deg = deg;
        while (rep--) {
            while(tmp_deg >= 0) {
                add(5, tmp_deg, sum);
                --tmp_deg;
            }
            sum = sum % MASK;
            tmp_deg = deg;
cout << "sum: " << sum << endl;
        }
    }

    if (z) {
        int rep = comb >= cod ? comb / cod * z : comb;
        int tmp_deg = deg;
        while (rep--) {
            while(tmp_deg >= 0) {
                add(6, tmp_deg, sum);
                --tmp_deg;
            }
            sum = sum % MASK;
            tmp_deg = deg;
cout << "sum: " << sum << endl;
        }
    }
}


int solve(int x, int y, int z) {
    ULONG sum = 0;

    for (int i = 0; i <= x; ++i) {
        for (int j = 0; j <= y; ++j) {
            for (int k = 0; k <= z; ++k) {
                solve_partially(i, j, k, sum);
            }
        }
    }

    return (int)(sum % MASK);
}






int main(int argc, const char* argv[]) {

    int x, y, z;
    cin >> x >> y >> z;

    cout << solve(x, y, z) << endl;

//    ULONG sum = 0;
//    solve_partially(x, y, z, sum);
//    cout << sum << endl;

    return 0;
}
