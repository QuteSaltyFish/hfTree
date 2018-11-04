//
//  hfTree.hpp
//  hfTree
//
//  Created by Mingke Wang on 2018/11/4.
//  Copyright © 2018 Mingke Wang. All rights reserved.
//

#ifndef hfTree_hpp
#define hfTree_hpp

#include <iostream>
using namespace std;

template <class T>
class hfTree
{
private:
    struct Node   //数组中的元素类型
    {
        T data; //节点值
        int weight; //节点的权值
        int parent, left, right;    //父节点以及左右儿子的下标地址
    };
    
    Node * elem;
    int length;
    
public:
    struct hfCode    //保存哈夫曼编码的类型
    {
        T data;     //待编码的字符
        string code;    //对应的哈夫曼编码
    };
    
    hfTree(const T *x, const int *w, int size);
    void getCode(hfCode result[]);  //从哈夫曼树生成哈夫曼编码
    ~hfTree(){delete [] elem;}
};

template <class T>
hfTree<T>::hfTree(const T *v, const int *w, int size)
{
    const int MAX_INT = 32767;
    int min1, min2; //最小树，次小树的权值
    int x,y;    //最小树，次小树的下标
    
    //置初值
    length = 2 * size;  //需要生成length-1个新的树d节点，还有一个是原始树根节点（不用于存储）。
    elem = new Node[length];
    for (int i = size; i<length; ++i)
    {
        elem[i].weight = w[i-size];
        elem[i].data = v[i-size];
        elem[i].parent = elem[i].left = elem[i].right = 0;
    }
    
    //归并森林中的树
    //每一次循环存储一个新生成的树的节点，原来已有的
    for (int i =size - 1; i>0; --i)
    {
        min1= min2 = MAX_INT;
        x = y = 0;
        for (int j = i+1; j<length; ++j)
        {
            //对于游离的树（不包括已经用过的树的叶子结点）
            if (elem[j].parent == 0)
            {
                if (elem[j].weight < min1)  //元素j最小
                {
                    //把上一个最小值的信息赋给现在的次小值
                    min2 = min1;
                    min1 = elem[j].weight;
                    x = y;
                    y = j;
                }
                else if (elem[j].weight < min2)     //元素j次小
                {
                    //更换次小元素的信息
                    min2 = elem[j].weight;
                    x= j;
                }
            }
        }
        elem[i].weight = min1 + min2;
        elem[i].left = x;
        elem[i].right = y;
        elem[i].parent = 0;
        elem[x].parent = i;
        elem[y].parent = i;
    }
}


template <class T>
void hfTree<T>::getCode(hfCode *result)
{
    int size = length /2;
    int p,s;    //s是追溯过程中正在处理的结点，p是s的父节点的下标
    
    for ( int i = size; i<length; ++i)
    {
        result[i-size].data = elem[i].data;
        result[i-size].code = "";
        p = elem[i].parent;
        s=i;
        
        //开始向根溯源
        while(p)
        {
            if (elem[p].left == s)
                result[i-size].code = '0' + result[i-size].code;    //在code前加一个0
            else
                result[i-size].code = '1' + result[i-size].code;    //在code前加一个1
            s = p;
            p = elem[p].parent;
        }
    }
}
#endif /* hfTree_hpp */
