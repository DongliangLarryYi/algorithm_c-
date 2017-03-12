//
//  main.cpp
//  check_project
//
//  Created by Dongliang Yi on 1/7/17.
//  Copyright © 2017 Dongliang Yi. All rights reserved.
//

#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
    type(type),
    position(position)
    {}
    
    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }
    
    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);
    
    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];
        
        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            Bracket new_data(next,position);
            opening_brackets_stack.push(new_data);
            
        }
        
        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if (opening_brackets_stack.empty()) {
                Bracket new_data(next,position);
                opening_brackets_stack.push(new_data);
                position = text.length();
            }
            else
            {
                Bracket top(opening_brackets_stack.top());
                opening_brackets_stack.pop();
                if ((top.type == '(' & next !=')') |(top.type == '[' & next !=']') |(top.type == '{' & next !='}')) {
                    Bracket new_data(next,position);
                    opening_brackets_stack.push(new_data);
                    position = text.length();
                }
                
            }
        }
    }
    
    // Printing answer, write your code here
    if (opening_brackets_stack.empty()) {
        std::cout << "Success" <<std::endl;
    }
    else
    {
        Bracket top(opening_brackets_stack.top());
        std::cout << top.position + 1 <<std::endl;
    }
    
    
    
    return 0;
}
