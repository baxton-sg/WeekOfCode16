

#include <iostream>

using namespace std;


inline
int abs(int v) {
    int mask = (unsigned int)v >> 31;
    return (mask ^ v) - mask;
}


inline
void solve(const int* A, int size, int L, int R) {
    int cur = L-1;
    int end = R-1;
    int sum = abs(A[cur++]);

    for (; cur <= end;)
        sum = abs(sum + A[cur++]);

    cout << (sum & 1 ? "Odd" : "Even") << "\n"; 
}


int main(int argc, const char* argv[]) {

    const int NMAX = 100000;

    int N, Q, L, R;
    int A[NMAX]; 

    cin >> N >> Q;
   
    for (int i = 0; i < N ; ++i) {
        cin >> A[i];
    }

    while(Q) {
        cin >> L >> R;

        solve(A, N, L, R);

        --Q;
    }

    return 0;
}
