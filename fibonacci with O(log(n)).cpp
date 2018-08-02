//  Fibonacci
//  Created by Dongliang Yi on 9/21/16.
//  Copyright © 2016 Dongliang Yi. All rights reserved.

#include <iostream>

// This function has the smallest running time, and it can calculate billinoth fabonacci number's last 6 digits.
long long solution(int N)
{
    //pleaser refer to https://ronzii.wordpress.com/2011/07/09/using-matrix-exponentiation-to-calculated-nth-fibonacci-number/
    // I just module the intermedia result and in this way, we can alwasy get the right last 6 digits
    long long fib[2][2]= {{1,1},{1,0}},ret[2][2]= {{1,0},{0,1}},tmp[2][2]= {{0,0},{0,0}};
    int i,j,k;
    while(N)
    {
        //Below equations are based on fabonacci identical equations, please refer to https://en.wikipedia.org/wiki/Fibonacci_number
        if(N&1)
        {
            //memset(tmp,0,sizeof tmp);
            tmp[0][0]= 0;
            tmp[0][1]= 0;
            tmp[1][0]= 0;
            tmp[1][1]= 0;
            std::cout << tmp << "\n";
            for(i=0; i<2; i++)
                for(j=0; j<2; j++)
                    for(k=0; k<2; k++)
                        tmp[i][j]=(tmp[i][j]%1000000+ret[i][k]%1000000*fib[k][j])%1000000;
            for(i=0; i<2; i++)
                for(j=0; j<2; j++)
                    ret[i][j]=tmp[i][j]%1000000;
        }
        
        //Below equations are based on fabonacci identical equations, please refer to https://en.wikipedia.org/wiki/Fibonacci_number
        tmp[0][0]= 0;
        tmp[0][1]= 0;
        tmp[1][0]= 0;
        tmp[1][1]= 0;
        for(i=0; i<2; i++)
            for(j=0; j<2; j++)
                for(k=0; k<2; k++)
            tmp[i][j]=(tmp[i][j]%1000000+fib[i][k]%1000000*fib[k][j]%1000000);
        for(i=0; i<2; i++)
            for(j=0; j<2; j++)
                fib[i][j]=tmp[i][j]%1000000;
        N/=2;
    }
    return (ret[0][1])%1000000;
}

unsigned long long int Fib5(int index)
{
    if(index<1)
    {
        return-1;
    }
    long long int a1=1,a2=1,a3=1;
    for(int i=0;i<index-2;i++)
    {
        a3=a1+a2;
        a1=a2;
        a2=a3;
    }
    return a3;
}

unsigned long long Fibonacci(int n){
    unsigned long long x = 1, y = 1, a = 0, b = 1,t;
    while (n>0)
    {
        if (n & 1){
            t = a*x + b*y;
            a = x*(b - a) + a*y;
            b = t;
        }
        t = 2 * x*y - x*x;
        y = x*x + y*y;
        x = t;
        n >>= 1;
    }
    return a;
}

int main(int argc, const char * argv[])
{
    clock_t start, finish;
    double duration;
    start = clock();
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    long i = 10000;
    std::cout <<"Result: "<< Fibonacci(i) << "\n";
    std::cout <<"Result: "<< Fib5(i) << "\n";
    std::cout <<"Result: "<< solution(i) << "\n";
    std::cout <<"Result: "<< solution2(i) << "\n";
    return 0;
}
