#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Node {
    unordered_map<char, Node*> children;
    int count;
    Node() { count = 0; }
};

class Trie {
private:
    Node *_root;
public:
    Trie() { _root = new Node(); }
    // add string
    void add(string str) {
        Node *node = _root;
        for (char c : str) {
            if (node->children.find(c) == node->children.end()) {
                Node *newNode = new Node();
                node->children[c] = newNode;
                node = newNode;
            } else {
                node = node->children[c];
            }
            node->count++;
        }
    }
    // find string
    int find(string str) {
        Node *node = _root;
        for (char c : str) {
            if (node->children.find(c) == node->children.end()) {
                return 0;
            } else {
                node = node->children[c];
            }
        }
        return node->count;
    }
};

int main(){
    int n;
    cin >> n;
    
    Trie Contact;
    
    for(int a0 = 0; a0 < n; a0++){
        string op;
        string contact;
        cin >> op >> contact;
        
        // action based on different order
        if (op == "add") {
        Contact.add(contact);
      } else {
        cout << Contact.find(contact) << endl;
      }
        
        
    }
    return 0;
}
