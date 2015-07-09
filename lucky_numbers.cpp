

#include <iostream>
#include <cstring>
#include <set>
#include <algorithm>
#include <cmath>
#include <memory>


using namespace std;

typedef unsigned long long ULONG;

const ULONG MASK = 1000000000 + 7;
const int MAX_NUMBERS = 100 * 100 * 100;



struct data {
    int size;
    unique_ptr<char> num;

    data(int s) :
        size(s),
        num(new char[size])
    {}
    data(const data& rhs) {
        size = rhs.size;
        num = unique_ptr<char>(new char[size]);
        memcpy(num.get(), rhs.num.get(), size);
    }

    template<typename T>
    operator T* () {return (T*)num;}

    const char& operator[] (size_t i) const { return num.get()[i];}
    char& operator[] (size_t i) { return num.get()[i];}
};

bool operator<(const data& d1, const data& d2) {
    if (d1.size < d2.size)
        return true;

    if (d1.size > d2.size)
        return false;

    for (int i = 0; i < d1.size; ++i)
        if (d1[i] > d2[i])
            return false;
        else if (d1[i] < d2[i])
            return true;

    return false;
}



ostream& operator<< (ostream& os, const data& d) {
    os /*<< "data d;" << endl
       << "d.size = " << d.size << ";" << endl */
       << "d.num = {";
    for (int i = 0; i < d.size; ++i)
        os << (int)d[i] << ",";
    os << "};" << endl;

    return os;
}

size_t fill_numbers(int x, int y, int z, data& vec) {
    size_t size = x + y + z;
    size_t cur = 0;

    vec.size = size;

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


int get_num(const data& numbers) {
    int result = 0;
    for (size_t i = 0; i < numbers.size; ++i)
        result = result * 10 + numbers[i];

    return result;
}






ULONG add(int num, int num_zeros, ULONG& sum) {
    if (num_zeros <= 8) {
        sum += num * pow(10, num_zeros);

        return sum % MASK;
    }

    int mul = num_zeros / 8; // 8 <= 100M
    int deg = num_zeros - mul * 8;
    int val = num * pow(10, deg) * mul * 999307;

    sum += val;

    return sum % MASK;
}


ULONG add(const data& num, ULONG& sum) {
    int num_zeros = num.size - 1;

    for (int i = 0; i < num.size; ++i) {
        int n = num[i];
        sum = add(n, num_zeros--, sum);
    }

    return sum % MASK;
}


void get_sum(data& numbers, set<data>& memo, size_t current, ULONG& sum) {

    if (current >= numbers.size)
        return;


    get_sum(numbers, memo, current+1, sum);


    for (size_t i = current+1; i < numbers.size; ++i) {
        if (numbers[current] == numbers[i])
            continue;

        swap(numbers[current], numbers[i]);

        if (memo.end() == memo.find(numbers)) {
            memo.insert(numbers);
            sum = add(numbers, sum);

            get_sum(numbers, memo, current+1, sum);
        }

        swap(numbers[current], numbers[i]);
    }

}


int solve(int x, int y, int z) {
    ULONG sum = 0;

    set<data> memo;

    for (int i = 0; i <= x; ++i) {
        for (int j = 0; j <= y; ++j) {
            for (int k = 0; k <= z; ++k) {
                size_t size = i + j + k;
                data numbers(size);
                fill_numbers(i, j, k, numbers);

                if (size) {
                     memo.insert(numbers);
                     sum = add(numbers, sum);

                     get_sum(numbers, memo, 0, sum);
                }

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

