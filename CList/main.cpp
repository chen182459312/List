//
//  main.cpp
//  CList
//
//  Created by chentao on 17/1/24.
//  Copyright © 2017年  All rights reserved.
//

#include <iostream>
#include "CList.hpp"

int main(int argc, const char * argv[]) {
    CList<char> list;
    char item = 'A';
    char itemInsert = item;
    for(int index = 0; index < 4; index++) {
        itemInsert = item + index;
        list.InsertItem(index, itemInsert);
    }
    
    const Node<char>*itm = list.ItemWithIndex(0);
    
    list.PrintList();
    list.RevertList();
    list.PrintList();
    
    return 0;
}
