

#include <iostream>
#include <cmath>


using namespace std;

typedef unsigned long long ULONG;
typedef long long LONG;

const ULONG MASK = 1000000000 + 7;




void add(int num, int num_zeros, ULONG& sum) {
    ULONG ll = 8;
    ULONG mod = (ULONG)pow(10, ll) % MASK;

    int mul = num_zeros / ll;
    int deg = num_zeros - mul * ll;

    ULONG val = num * (ULONG)pow(10, deg);

    for (int i = 0; i < mul; ++i) {
        val *= mod;
        val %= MASK;
    }

    sum = (sum + val) % MASK;
}

inline
bool is_div(int n, int d) {
    return 0 == (n % d);
}



void reduce(ULONG& comb, int x, int y, int z) {
    while(is_div(x, 2) && is_div(y, 2) && is_div(z, 2)) {
        comb /= 2;
        x /= 2;
        y /= 2;
        z /= 2;
    }

    while(is_div(x, 3) && is_div(y, 3) && is_div(z, 3)) {
        comb /= 3;
        x /= 3;
        y /= 3;
        z /= 3;
    }

    while(is_div(x, 5) && is_div(y, 5) && is_div(z, 5)) {
        comb /= 5;
        x /= 5;
        y /= 5;
        z /= 5;
    }

    while(is_div(x, 7) && is_div(y, 7) && is_div(z, 7)) {
        comb /= 7;
        x /= 7;
        y /= 7;
        z /= 7;
    }
}



ULONG get_comb(int cod, int x, int y, int z) {
    double res = 1;
    while (cod && x && y && z) {
        res *= cod--;
        res /= x--;
        res /= y--;
        res /= z--;
    }

    while(cod && x) {
        res *= cod--;
        res /= x--;
    }

    while(cod && y) {
        res *= cod--;
        res /= y--;
    }

    while(cod && z) {
        res *= cod--;
        res /= z--;
    }

    while(cod)
        res *= cod--;

   
    return (ULONG)res;        
}


void solve_partially(int x, int y, int z, ULONG& sum) {

    if (0 == (x + y + z))
        return;

    LONG deg = x + y + z - 1;
    LONG cod = x + y + z;

    ULONG comb = get_comb(cod, x, y, z);
    if (comb >= cod)
        reduce(comb, x, y, z);


    if (x) {
        LONG rep = comb >= cod ? comb / cod * x : comb;
        LONG tmp_deg = deg;
        //while (rep--) {
            ULONG tmp_sum = 0;
            while(tmp_deg >= 0) {
                add(4, tmp_deg, tmp_sum);
                --tmp_deg;
            }
            sum += (tmp_sum * rep) % MASK;
            sum = sum % MASK;
        //    tmp_deg = deg;
        //}
    }

    if (y) {
        LONG rep = comb >= cod ? comb / cod * y : comb;
        LONG tmp_deg = deg;
        //while (rep--) {
            ULONG tmp_sum = 0;
            while(tmp_deg >= 0) {
                add(5, tmp_deg, tmp_sum);
                --tmp_deg;
            }
            sum += (tmp_sum * rep) % MASK;
            sum = sum % MASK;
        //    tmp_deg = deg;
        //}
    }

    if (z) {
        LONG rep = comb >= cod ? comb / cod * z : comb;
        LONG tmp_deg = deg;
        //while (rep--) {
            ULONG tmp_sum = 0;
            while(tmp_deg >= 0) {
                add(6, tmp_deg, tmp_sum);
                --tmp_deg;
            }
            sum += (tmp_sum * rep) % MASK;
            sum = sum % MASK;
        //    tmp_deg = deg;
        //}
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
