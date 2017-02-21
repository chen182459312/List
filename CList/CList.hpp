//
//  CList.hpp
//  CList
//
//  Created by chentao on 17/1/24.
//  Copyright © 2017年. All rights reserved.
//

#ifndef CList_hpp
#define CList_hpp

#include <stdio.h>
#include <memory.h>
#include <iostream>
using namespace std;

template<class T>
class Node {
public:
    Node() {
        pNext = nullptr;
    }
    ~Node() {
    }
public:
    Node *pNext;
    T data;
};

template<class T>
class CList{
    
public:
    CList();
    explicit CList(const T &itm);
    ~CList();
    const size_t ListLength();
    const Node<T>* ListHeadItem();
    const Node<T>* ListTailItem();
    void CreatList(const T &itm);
    bool InsertItem(const size_t index, const T &item);//In particular, note the side effects of C ++ implicit type conversion, the use of the index parameter type must be matched to the size_t
    const Node<T>* ItemWithIndex(const size_t index);
    void PushTailItem(const T &itm);
    bool DeleteItem(const size_t index);
    void RevertList();//Inverts a single linked list in place
    void ClearList();
    bool IsEmpty();
    void PrintList();

private:
    Node<T> *m_pHead;//List head
    Node<T> *m_pTail;//Table tail node; the use of the end of the table node, to avoid the end of the table inserted in the list again when the traversal chain, to improve efficiency
    size_t m_length;//List length [number of elements] to avoid seeking the length of the list again when traversing the linked list, to improve efficiency
};

template<class T>
CList<T>::CList() {
    m_pHead = nullptr;
    m_pTail = nullptr;
    m_length = 0;
}

template<class T>
CList<T>::CList(const T &itm) {
    CreatList(itm);
}

template<class T>
CList<T>::~CList() {
    ClearList();
}

template<class T>
void CList<T>::CreatList(const T &itm) {
    InsertItem(0, itm);
}

template<class T>
const Node<T>* CList<T>::ListHeadItem() {
    return m_pHead;
}

template<class T>
const Node<T>* CList<T>::ListTailItem() {
    return m_pTail;
}

template<class T>
const size_t CList<T>::ListLength() {
    return m_length;
}

template<class T>
bool CList<T>::InsertItem(const size_t index, const T &item) {
    bool bInsert = false;
    const size_t length = ListLength();
    do {
        if (index > length) {//The index number crosses
            break;
        }
        if (0 == length && 0 == index) {//empty list
            Node<T> *pNodeNew = new Node<T>;
            memset(pNodeNew, 0, sizeof(Node<T>));
            pNodeNew->data = item;
            m_pHead = pNodeNew;
            m_pTail = pNodeNew;
            m_length++;
            bInsert = true;
            break;
        }
        if (0 == index) {//insert with head
            Node<T> *pHead = m_pHead;
            Node<T> *pNodeNew = new Node<T>;
            memset(pNodeNew, 0, sizeof(Node<T>));
            pNodeNew->data = item;
            pNodeNew->pNext = pHead;
            m_pHead = pNodeNew;
            m_length++;
            bInsert = true;
            break;
        }
        if (index == length) {//push with tail.
            Node<T> *pNode = m_pTail;
            Node<T> *pNodeNew = new Node<T>;
            memset(pNodeNew, 0, sizeof(Node<T>));
            pNodeNew->data = item;
            pNode->pNext = pNodeNew;
            m_pTail = pNodeNew;
            m_length++;
            bInsert = true;
            break;
        }
        //Insert the item in the list middle
        size_t indexFind = 0;
        Node<T> *pNode = m_pHead;
        Node<T> *pNewNode = new Node<T>();
        pNewNode->data = item;
        while(pNode != nullptr) {
            if (indexFind == index-1) {//Note that minus 1
                Node<T> *pTmp = pNode->pNext;
                pNode->pNext = pNewNode;
                pNewNode->pNext = pTmp;
                m_length++;
                bInsert = true;
                break;
            }
            pNode = pNode->pNext;
            indexFind++;
        }
    } while (false);
    return bInsert;
}

template<class T>
void CList<T>::PushTailItem(const T &itm) {
    size_t length = ListLength();
    InsertItem(length, itm);
}

template<class T>
const Node<T>* CList<T>::ItemWithIndex(const size_t index) {
    const size_t length = ListLength();
    Node<T> *pNode = nullptr;
    size_t indexCourse = 0;
    do {
        if (index > length-1) {
            break;
        }
        pNode = m_pHead;
        while (pNode) {
            if (index == indexCourse) {
                break;
            }
            pNode = pNode->pNext;
            indexCourse++;
        }
    } while (false);
    return pNode;
}

template<class T>
bool CList<T>::DeleteItem(const size_t index) {
    bool bDelete = false;
    Node<T> *pNode = nullptr;
    Node<T> *pDelete = nullptr;
    size_t indexCourse = 0;
    size_t length = ListLength();
    do {
        if (0 == length || index > length-1) {
            break;
        }
        if(0 == index) {//delete head item
            pNode = m_pHead;
            m_pHead = pNode->pNext;
            pDelete = pNode;
            delete pDelete;
            pDelete = nullptr;
            m_length--;
            if (0 == m_length) {
                m_pTail = nullptr;
                m_pHead = nullptr;
            }
            bDelete = true;
            break;
        }
        if (index == length-1) {//delete taile item
            pNode = m_pHead;
            while (pNode->pNext != nullptr) {
                if (indexCourse == length-2) {
                    m_pTail = pNode;
                }
                pNode = pNode->pNext;
                indexCourse++;
            }
            m_pTail->pNext = nullptr;//note! disconnect
            delete pNode;
            pNode = nullptr;
            
            m_length--;
            if (0 == m_length) {
                m_pHead = nullptr;
                m_pTail = nullptr;
            }
            bDelete = true;
            break;
        }
        //delete item in list middle
        Node<T> *pNode = m_pHead;
        while (pNode != nullptr) {
            if (indexCourse == index-1) {
                pDelete = pNode->pNext;
                Node<T> *pNext = pDelete->pNext;
                delete pDelete;
                pDelete = nullptr;
                pNode->pNext = pNext;
                m_length--;
                bDelete = true;
                break;
            }
            indexCourse++;
            pNode = pNode->pNext;
        }
    } while (false);
    return bDelete;
}

template<class T>
void CList<T>::RevertList() {
    if (IsEmpty()) {
        return;
    }
    Node<T> *pDummy = new Node<T>;
    memset(pDummy, 0, sizeof(Node<T>));
    Node<T> *pPreNode = m_pHead;
    Node<T> *pCurNode = pPreNode->pNext;
    pDummy->pNext = pPreNode;
    m_pTail = pPreNode;
    m_pTail->pNext = nullptr;
    while (pCurNode) {
        pPreNode->pNext = pCurNode->pNext;
        pCurNode->pNext = pDummy->pNext;
        pDummy->pNext = pCurNode;
        pCurNode = pPreNode->pNext;
    }
    m_pHead = pDummy->pNext;
    
    delete pDummy;
    pDummy = nullptr;
}

template<class T>
void CList<T>::ClearList() {
    Node<T> *pNode = m_pHead;
    while (pNode) {
        Node<T> *pDelete = pNode;
        delete pDelete;
        pDelete = nullptr;
        pNode = pNode->pNext;
        pDelete = pNode;
    }
    m_pHead = nullptr;
    m_pTail = nullptr;
    m_length = 0;
}

template<class T>
bool CList<T>::IsEmpty() {
    return 0 == m_length ? true : false ;
}

template<class T>
void CList<T>::PrintList() {
    Node<T> *node = m_pHead;
    size_t index = 0;
    if (node) {
        cout<<"\n********************list display:\n";
        while (node) {
            cout<<"index:"<<index<<" data:"<<node->data<<" ";
            index++;
            node = node->pNext;
        }
        cout<<"\n********************list display over!\n";
    }
    else {
        cout<<"empty list"<<endl;
    }
}

#endif
