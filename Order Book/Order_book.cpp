
//  Order_book
//  Created by Dongliang Yi on 1/14/17.
//  Copyright © 2017 Dongliang Yi. All rights reserved.
//  Thanks to Daniel Cao who provided part of this code

#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>

#define MAX_ID 100000 // at most 100000 orders
using namespace std;

// structure of an order which include id, side, price, size and related functions
class Order{
private:
    int id;
    char side;
    double price;
    int size;
public:
    // constructor function
    Order(int id , char side , double price , int size)
    {
        this->id = id;
        this->side = side;
        this->price = price;
        this->size = size;
    }
    
    // get id
    int getId()
    {
        return this->id;
    }
    
    // get order size
    int getOrderSize()
    {
        return this->size;
    }
    
    // get order price
    double getPrice()
    {
        return this->price;
    }
    
    // get side 'buy' or 'sell'
    char getSide()
    {
        return this->side;
    }
    
    // change order size
    void setSize(int size)
    {
        this->size = size;
    }
};

// structure of orders with same price and side
class OrderSameLevel{
private:
    double price;
    int size;
    char side;
    list<Order> SameLevel;
    
public:
    // construction function
    OrderSameLevel(char side, double price)
    {
        this->price = price;
        this->size = 0;
        this->side = side;
        this->SameLevel.push_back(Order(0,side,price,0));
    }
    
    // get the total size of orders with same price and side
    void updateSize()
    {
        this->size = 0;
        for (std::list<Order>::iterator it = SameLevel.begin();it != SameLevel.end();it++)
        {
            this->size += it->getOrderSize();
        }
    }
    
    // add new order
    void addToLevel(Order order)
    {
        this->SameLevel.push_back(order);
        //this->updateSize();
        this->size += order.getOrderSize(); // add new order's size to total size.
    }
    
    // remove the specific order
    void cancelFromLevel(int id)
    {
        double size_delete = 0;
        for(std::list<Order>::iterator it = SameLevel.begin(); it!= SameLevel.end();)
        {
            if(it->getId() == id)
            {
                size_delete = it->getOrderSize();
                it = SameLevel.erase(it);
                break;
            }
            else
            {
                ++it;
            }
        }
        this->size -= size_delete;
    }
    
    void updateSingleOrderSize (int id, int newSize)
    {
        double size_delete = 0;
        
        for(std::list<Order>::iterator it = SameLevel.begin(); it!= SameLevel.end();)
        {
            if(it->getId() == id)
            {
                size_delete = it->getOrderSize();
                it->setSize(newSize);
                break;
            }
            else
            {
                ++it;
            }
        }
        //this->updateSize();
        this->size = this->size - size_delete + newSize;
    }
    
    // get the total size of the same level and side
    int getSize()
    {
        return this->size;
    }
    
    // get the price
    double getPrice()
    {
        std::list<Order>::iterator it = SameLevel.begin();
        return it->getPrice();
    }
    
    int getSide()
    {
        return this->side;
    }

};


class OrderBook{
    
private:
    list<OrderSameLevel> book;
    int depth;
    double array_of_id[MAX_ID]; // MAX_ID number of id for use
    
public:
    OrderBook()
    {
        this->depth = 0;
        for (int i = 0; i < MAX_ID; i++)
        {
            array_of_id[i] = 0.0;
        }
    }
    
    void add(int id, char side, double price, int size)
    {
        Order order1(id, side, price, size);
        array_of_id[id] = price;
        if (this->book.size() == 0)//if emply, create
        {
            book.push_back(OrderSameLevel(side, price));
            std::list<OrderSameLevel>::iterator it = book.begin();
            it->addToLevel(order1);
            depth++;
        }
        else // try to find the same level
        {
            
            bool found = false;
            OrderSameLevel neworderlevel(side,price);
            for (std::list<OrderSameLevel>::iterator it = book.begin();it != book.end();)
            {
                if (it->getPrice() == price)
                {
                    it->addToLevel(order1);
                    found = true;
                    break;
                }
                else it++;
            }
            
            if (found == false) //if there is now existing price level, create one
            {
                bool add_before_end = false;
                for (std::list<OrderSameLevel>::iterator it = book.begin();it != book.end();)
                {
                    if(it->getPrice() > neworderlevel.getPrice())
                    {
                        book.insert(it, neworderlevel);//the price is increasingly sorted
                        it--;
                        it->addToLevel(order1);
                        depth ++;
                        add_before_end = true;
                        break;
                    }
                    else
                    {
                        it++;
                    }
                }
                if (add_before_end == false) //if this is the order of the highest price, push_back
                {
                    book.push_back(neworderlevel);
                    book.back().addToLevel(order1);
                    depth++;
                }
            }
        }
    }
    
    void remove (int order_id)
    {
        double price_level_to_go = array_of_id[order_id];
        if (price_level_to_go > 0)
        {
            for (std::list<OrderSameLevel>::iterator it = book.begin();it != book.end();)
            {
                if (it->getPrice() == price_level_to_go)
                {
                    it->cancelFromLevel(order_id);
                    break;
                }
                else it++;
            }
        }
    }
    
    void modify(int order_id, int new_size)
    {
        double price_level_to_go = array_of_id[order_id];
        if (price_level_to_go > 0)
        {
            for (std::list<OrderSameLevel>::iterator it = book.begin();it != book.end();)
            {
                if (it->getPrice() == price_level_to_go)
                {
                    it->updateSingleOrderSize(order_id,new_size);
                    break;
                }
                else it++;
            }
        }
    }
    
    int getDepth()
    {
        return this->depth;
    }
    
    double get_price(int level)
    {
        std::list<OrderSameLevel>::iterator it_beg = book.begin();
        std::list<OrderSameLevel>::iterator it_end = book.end();
        it_end--; //important to point to the right data
        int lev = level;
        char side_book = it_beg->getSide();
        if (side_book == 'S') //level of sell
        {
            while (lev >1)
            {
                it_beg++;
                lev--;
            }
            cout <<it_beg->getPrice()<<endl;
            return it_beg->getPrice();
        }
        else // level of buy
        {
            while (lev >1)
            {
                it_end--;
                lev--;
            }
            cout <<it_end->getPrice()<<endl;
            return it_end->getPrice();
        }

    }
    
    int get_size(int level)
    {
        std::list<OrderSameLevel>::iterator it_beg = book.begin();
        std::list<OrderSameLevel>::iterator it_end = book.end();
        it_end--;
        int lev = level;
        char side_book = it_beg->getSide();
        if (side_book == 'S') //level of sell
        {
            while (lev >1)
            {
                it_beg++;
                lev--;
            }
            cout <<it_beg->getSize()<<endl;
            return it_beg->getSize();
        }
        else // level of buy
        {
            while (lev >1)
            {
                it_end--;
                lev--;
            }
            cout <<it_end->getSize()<<endl;
            return it_end->getSize();
        }
    }
};

int main (int argc, const char * argv[])
{
    OrderBook sell, buy;
    // if input file through terminal
    //ifstream input_file(argv[1]);
    ifstream input_file("/Users/Larry/Documents/CPP_Code/compiled/Debug/order_data1.txt");
    string od_name;
    string od_name2;
    char side;
    double price;
    int size;
    int id;
    int level;
    
    while (!input_file.eof())
    {
        input_file >> od_name;
        //to find which operation to do by reading a new input
        if (od_name == "add")
        {
            input_file >> id;
            input_file >> side;
            input_file >> price;
            input_file >> size;
            if (side == 'S')
            {
                sell.add(id , side, price, size);
            }
            else
                buy.add(id , side, price, size);
        }
        if (od_name == "modify") {//if it is a modify
            input_file >> id;
            input_file >> size;
            sell.modify(id, size);
            buy.modify(id, size);
        }
        if (od_name == "remove")
        { //if it is a remove
            input_file >> id;
            sell.remove(id);
            buy.remove(id);
        }
        if (od_name == "get")
        {
            input_file >> od_name2;
            if (od_name2 == "price")
            {
                input_file >> side;
                input_file >> level;
                if (side == 'S')
                {
                    sell.get_price(level);
                }
                else
                {
                    buy.get_price(level);
                }
            }
            else
            {
                input_file >> side;
                input_file >> level;
                if (side == 'S')
                {
                    sell.get_size(level);
                }
                else
                    buy.get_size(level);
            }
        }
    }
    return 0;
}
