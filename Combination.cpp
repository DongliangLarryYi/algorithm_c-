//
//  main.cpp
//  combination
//
//  Created by Dongliang Yi on 9/21/16.
//  Copyright © 2016 Dongliang Yi. All rights reserved.
//

#include <iostream>

// this has a running time
long long solution(int N, int K) {
    // write your code in C++11 (g++ 4.8.2)
    if ( ( N < 0) || (K < 0)) {
        return -1;
    }
    if (K > N) {
        return -1;
    }
    long long r = 1;
    long long  NK = N - K;
    long long  min = (K>NK)? NK:K;
    for (long long d = 1; d <= min; ++d) {
        r = r * N / d;
        --N;
    }
    if (r > 1000000000) {
        return -1;
    }
    return r;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    clock_t start, finish;
    double duration;
    //double fibonacci;
    unsigned long long combination;
    start = clock();
    combination = choose(20, 15);
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    int i = 1000000;
    int j = 1;
    //std::cout <<"Result: "<< choose(i, j) << "\n";
    std::cout <<"Result: "<< solution(i, j) << "\n";
    std::cout <<"Time: " << duration << "\n";
    return 0;
}
