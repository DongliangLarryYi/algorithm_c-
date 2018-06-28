//  main.cpp
//  build_heap
//  Created by Dongliang Yi on 1/21/17.
//  Copyright © 2017 Dongliang Yi. All rights reserved.

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
private:
    vector<int> data_;
    vector< pair<int, int> > swaps_;

    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }
    
    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for(int i = 0; i < n; ++i)
            cin >> data_[i];
    }
    
    void SiftDown(int i)
    {
        int minIndex = i;
        int l_ = i*2 + 1;
        if ((l_ < data_.size()) && (data_[l_] < data_[minIndex])) {
            minIndex = l_;
        }
        int r_ = i*2+2;
        if ((r_< data_.size()) && (data_[r_] < data_[minIndex])) {
            minIndex = r_;
        }
        if (i != minIndex) {
            swap(data_[i], data_[minIndex]);
            swaps_.push_back(make_pair(i, minIndex));
            SiftDown(minIndex);
        }
    }
    
    void GenerateSwaps() {
        swaps_.clear();
        // The following naive implementation just sorts
        // the given sequence using selection sort algorithm
        // and saves the resulting sequence of swaps.
        // This turns the given array into a heap,
        // but in the worst case gives a quadratic number of swaps.
        //
        // TODO: replace by a more efficient implementation
        // use the algorithm to siftdown
        int up_limit = floor(data_.size()/2);
        for (int i = up_limit; i >= 0; i--) {
            SiftDown(i);
        }
    }
    
public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
