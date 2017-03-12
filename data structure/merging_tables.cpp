//
//  main.cpp
//  merging_tables
//
//  Created by Dongliang Yi on 1/22/17.
//  Copyright © 2017 Dongliang Yi. All rights reserved.
//

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
    int size, parent, rank;
    
    DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
    int size;
    int max_table_size;
    vector <DisjointSetsElement> sets;
    
    DisjointSets(int size): size(size), max_table_size(0), sets(size) {
        for (int i = 0; i < size; i++)
            sets[i].parent = i;
    }
    
    int getParent(int table) {
        // find parent and compress path
        int index_table = table;
        while(index_table != sets[index_table].parent)
        {
            index_table = sets[index_table].parent;
        
        }
        
        return index_table;
        
    }
    
    void merge(int destination, int source) {
        int realDestination = getParent(destination);
        int realSource = getParent(source);
        if (realDestination != realSource) {
            // merge two components
            // use union by rank heuristic
            // update max_table_size
            
            int Des_id = getParent(realDestination);
            int Sou_id = getParent(realSource);
            
            int sum_size = 0;
            
            if(Des_id == Sou_id)
            {}
            else{
            if(sets[Des_id].rank > sets[Sou_id].rank)
            {
                sets[Sou_id].parent = Des_id;
                sum_size = sets[Des_id].size + sets[Sou_id].size;
                sets[Des_id].size = sum_size;
            
            }
            else{
                sets[Des_id].parent = Sou_id;
                sum_size = sets[Des_id].size + sets[Sou_id].size;
                sets[Sou_id].size = sum_size;
                if(sets[Des_id].rank == sets[Sou_id].rank)
                    sets[Sou_id].rank += 1;
            
            }
                if(sum_size > max_table_size)
                    max_table_size = sum_size;
                
            
            }
            
            
            
            
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    DisjointSets tables(n);
    for (auto &table : tables.sets) {
        cin >> table.size; //each table's size
        tables.max_table_size = max(tables.max_table_size, table.size); // biggest in the tables
    }
    
    for (int i = 0; i < m; i++) {
        int destination, source;
        cin >> destination >> source;
        // get the real index of the address
        --destination;
        --source;
        
        tables.merge(destination, source);
        cout << tables.max_table_size << endl;
    }
    
    return 0;
}
