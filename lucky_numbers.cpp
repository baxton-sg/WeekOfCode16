

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>


using namespace std;

typedef unsigned long long ULONG;

const int MASK = 1000000000 + 7;




void fill_numbers(int x, int y, int z, vector<int>& vec) {
    while (x && y && z) {
        vec.push_back(4);
        vec.push_back(5);
        vec.push_back(6);

        --x;
        --y;
        --z;
    }

    while (x) {
        vec.push_back(4);
        --x;
    }

    while (y) {
        vec.push_back(5);
        --y;
    }

    while (z) {
        vec.push_back(6);
        --z;
    }
}


int get_num(vector<int>& numbers) {
    int result = 0;
    for (size_t i = 0; i < numbers.size(); ++i)
        result = result * 10 + numbers[i];

    return result;
}


void get_sum(vector<int>& numbers, set<int>& memo, size_t current, ULONG& sum) {

    if (current >= numbers.size())
        return;

    for (size_t i = 0; i < numbers.size(); ++i) {
        swap(numbers[current], numbers[i]);

        int n = get_num(numbers);

        if (memo.end() == memo.find(n)) {
            memo.insert(n);
            sum += n;
        }

        get_sum(numbers, memo, current+1, sum);

        // restore
        swap(numbers[current], numbers[i]);
    }

}


int solve(int x, int y, int z) {
    ULONG sum = 0;

    vector<int> numbers;
    set<int> memo;

    for (int i = 0; i <= x; ++i) {
        for (int j = 0; j <= y; ++j) {
            for (int k = 0; k <= z; ++k) {
               fill_numbers(i, j, k, numbers);
               get_sum(numbers, memo, 0, sum);

               numbers.clear();
               memo.clear();
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
