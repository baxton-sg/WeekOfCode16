

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cmath>


using namespace std;

typedef unsigned long long ULONG;

const ULONG MASK = 1000000000 + 7;
const int MAX_NUMBERS = 100 * 100 * 100;




size_t fill_numbers(int x, int y, int z, vector<int>& vec) {
    size_t size = x + y + z;
    size_t cur = 0;

    while (x && y && z) {
        vec[cur+0] = 4;
        vec[cur+1] = 5;
        vec[cur+2] = 6;

        cur += 3;

        --x;
        --y;
        --z;
    }

    while (x) {
        vec[cur++] = 4;
        --x;
    }

    while (y) {
        vec[cur++] = 5;
        --y;
    }

    while (z) {
        vec[cur++] = 6;
        --z;
    }

    return size;
}


int get_num(vector<int>& numbers, size_t size) {
    int result = 0;
    for (size_t i = 0; i < size; ++i)
        result = result * 10 + numbers[i];

    return result;
}


void get_sum(vector<int>& numbers, size_t size, int init_val, unordered_set<int>& memo, size_t current, ULONG& sum) {

    if (current >= size)
        return;


    get_sum(numbers, size, init_val, memo, current+1, sum);


    for (size_t i = current+1; i < size; ++i) {
        if (numbers[current] == numbers[i])
            continue;


        int p1 = pow(10, size - current - 1),
            p2 = pow(10, size - i - 1);
        int tmp = init_val - (numbers[current] * p1) - (numbers[i] * p2) 
                           + (numbers[current] * p2) + (numbers[i] * p1);



        if (memo.end() == memo.find(tmp)) {
            memo.insert(tmp);
            sum += tmp;
        

            swap(numbers[current], numbers[i]);
            get_sum(numbers, size, tmp, memo, current+1, sum);
            swap(numbers[current], numbers[i]);
        }
    }

}


int solve(int x, int y, int z) {
    ULONG sum = 0;

    vector<int> numbers(MAX_NUMBERS, 0);
    unordered_set<int> memo;

    for (int i = 0; i <= x; ++i) {
        for (int j = 0; j <= y; ++j) {
            for (int k = 0; k <= z; ++k) {
                size_t size = fill_numbers(i, j, k, numbers);

                if (size) {
                     int n = get_num(numbers, size);
                     memo.insert(n);
                     sum += n;

                     get_sum(numbers, size, n, memo, 0, sum);
                }
            }
        }
    }

    return (int)(sum % MASK);
}






int main(int argc, const char* argv[]) {

    int x, y, z;
    cin >> x >> y >> z;

    cout << solve(x, y, z) << endl;

    return 0;
}
