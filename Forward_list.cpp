// Forward_list.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <vector>
#include <Forward_list>
#include <algorithm>
#include "Forward_list.hpp"

int main()
{

    Forward_list<int> my_list;
    
    my_list.push_front(6);

    std::cout << my_list.size();
}

