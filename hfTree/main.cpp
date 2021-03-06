//
//  main.cpp
//  hfTree
//
//  Created by Mingke Wang on 2018/11/4.
//  Copyright © 2018 Mingke Wang. All rights reserved.
//

#include <iostream>
#include "hfTree.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    char ch[] = {"aeistdn"};
    int w[] = {10, 15, 12, 3, 4, 13, 1};
    
    hfTree<char> tree(ch, w, 7);
    hfTree<char>::hfCode result[7];
    
    tree.getCode(result);
    
    for (int i=0; i<7; ++i)
    {
        cout<< result[i].data<<' '<<result[i].code<<endl;
    }
    
    cout<<tree.getDepth()<<endl;;
    for (int i=1; i<14;++i)
    {
//        if (tree.getParent(i)==0)
        {
            cout<<tree.getParent(i)<<' '<<tree.getData(i)<<' '<<tree.getLeftChild(i)<<' '<<tree.getRightChild(i)<<endl;
        }
    }
    
    
    tree.ShowTreeMap();

    return 0;
}
