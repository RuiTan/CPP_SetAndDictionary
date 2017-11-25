//
// Created by tanrui on 17-11-23.
//
/*
 * 关于依赖名有时间要好好看看
 */

#ifndef SET_LINKEDSET_H
#define SET_LINKEDSET_H

#include <cstdlib>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;
#define MAXSIZE 10000

template <class T> struct SetNode{
    T data;
    SetNode<T> *link;
    SetNode():link(nullptr){};
    SetNode(const T& x, SetNode<T> *next = nullptr):data(x), link(next){}
};

template <class T> class LinkedSet{
private:
    SetNode<T> *first, *last;
public:
    SetNode<T> *getFirst() const;
    SetNode<T> *getLast() const;
private:
    int setSize;
    LinkedSet(LinkedSet<T>& R);
public:
    inline int getSize(){return setSize;}
    LinkedSet(){first = last = new SetNode<T>;setSize = 0;}
    ~LinkedSet(){
        makeEmpty();
        delete first;
        first = last = nullptr;
    }
    void makeEmpty();
    bool addMember(const T& x);
    bool addMember(const vector<T>& x);
    bool delMember(const T& x);
    SetNode<T>* getMember(const T& x);
    LinkedSet<T>&operator = (LinkedSet<T>& R);
    LinkedSet<T>&operator + (LinkedSet<T>& R);
    LinkedSet<T>&operator - (LinkedSet<T>& R);
    LinkedSet<T>&operator * (LinkedSet<T>& R);
    bool Contains(T x);
    bool operator == (LinkedSet<T>& R);
    inline T& Min(){
        if (setSize == 0){
        }  else {
            return first->link->data;
        }
    };
    inline T& Max(){
        if (setSize == 0){
        }  else {
            return last->data;
        }
    };
    bool subSet(LinkedSet<T>& R);

    friend ostream&operator << (ostream &out, LinkedSet<T>& R){
        if (R.setSize == 0){
            out << "This is a null set!\n";
        }else{
            out << "{";
            SetNode<T>* temp = R.first->link;
            for (int i = 0; i < R.setSize; ++i) {
                out << temp->data;
                temp = temp->link;
                if (i!=R.setSize-1){
                    out << ",";
                }
            }
            out << "}\n";
        }
    }
};


template <class T>
LinkedSet<T>::LinkedSet(LinkedSet<T> &R) {
    makeEmpty();
    if (R.setSize == 0){
        return ;
    }
    SetNode<T> *tempThis = first = new SetNode<T>, *tempR = R.first->link;
    do {
        tempThis->link = new SetNode<T>(tempR->data);
        tempThis = tempThis->link;
        tempR = tempR->link;
    }while (tempR != nullptr);
    tempThis->link = nullptr;
    last = tempThis;
    setSize = R.setSize;
}

template <class T>
bool LinkedSet<T>::addMember(const vector<T> &x) {
//    vector<T>::iterator ix;
    auto ix = x.begin();
    while (ix != x.end()){
        addMember(*ix++);
    }
}

template <class T>
bool LinkedSet<T>::addMember(const T &x) {
    assert(setSize+1<MAXSIZE);
    if (Contains(x)){
        return false;
    }
    if (first == nullptr){
        first = new SetNode<T>;
        last = first;
    }
    SetNode<T> *flag = first;
    for (int i = 0; i < setSize; ++i) {
        if (flag->link->data > x){
            break;
        }
        flag = flag->link;
    }
    SetNode<T> *temp = new SetNode<T>(x);
    temp->link = flag->link;
    flag->link = temp;
    if (flag == last){
        last = temp;
    }
    setSize++;
    return true;
}

template <class T>
SetNode<T>* LinkedSet<T>::getMember(const T &x) {
    if(setSize == 0) return nullptr;
    SetNode<T>* temp = first->link;
    for (int i = 0; i < setSize; ++i) {
        if (temp->data == x){
            return temp;
        }else{
            temp = temp->link;
            continue;
        }
    }
    return nullptr;
}


template <class T>
void LinkedSet<T>::makeEmpty() {
    if (first == last){
        return;
    }
    SetNode<T> *temp = first->link, *tempPre;
    for (int i = 0; i < setSize; ++i) {
        tempPre = temp->link;
        temp->link = nullptr;
        delete temp;
        temp = tempPre;
    }
    setSize = 0;
    last = first;
    first->link = nullptr;
}

template <class T>
bool LinkedSet<T>::delMember(const T &x) {
    assert(first!=last);
    if (Contains(x)){
        SetNode<T> *temp = first->link, *tempPre = first;
        for (int i = 0; i < setSize; ++i) {
            if (temp->data == x){
                if (setSize == 1){
                    delete first;
                    first = last = nullptr;
                }
                tempPre->link = temp->link;
                if (temp == last){
                    last = tempPre;
                }
                delete temp;
                setSize--;
                return true;
            }
            tempPre = temp;
            temp = temp->link;
        }
    } else{
        return false;
    }
}

template <class T>
bool LinkedSet<T>::Contains(const T x) {
    return getMember(x) != nullptr;
}

template <class T>
LinkedSet<T> &LinkedSet<T>::operator=(LinkedSet<T> &R) {
    makeEmpty();
    if (R.setSize == 0){
        return *this;
    }
    SetNode<T> *tempThis = first = new SetNode<T>, *tempR = R.first->link;
    do {
        tempThis->link = new SetNode<T>(tempR->data);
        tempThis = tempThis->link;
        tempR = tempR->link;
    }while (tempR != nullptr);
    tempThis->link = nullptr;
    last = tempThis;
    setSize = R.setSize;
    return *this;
}

template <class T>
LinkedSet<T>& LinkedSet<T>::operator*(LinkedSet<T> &R) {
    LinkedSet<T> *intersection = new LinkedSet();
    if (first == last || R.first == R.last){
        return *intersection;
    }
    SetNode<T> *tempA = first->link, *tempB = R.first->link;
    while (tempA && tempB){
        if (tempA->data > tempB->data){
            tempB = tempB->link;
        } else if (tempA->data < tempB->data) {
            tempA = tempA->link;
        } else {
            intersection->addMember(tempA->data);
            tempA = tempA->link;
            tempB = tempB->link;
        }

    }
    return *intersection;
}

template <class T>
LinkedSet<T>& LinkedSet<T>::operator+(LinkedSet<T> &R) {
    LinkedSet<T> *crowding;
    if (setSize == 0 && R.setSize == 0){
        crowding->setSize = 0;
        return *crowding;
    }else if(setSize == 0){
        crowding = new LinkedSet(R);
    }else if(R.setSize == 0){
        crowding = new LinkedSet(*this);
    }else {
        crowding = new LinkedSet;
        SetNode<T>* temp = first->link;
        for (int i = 0; i < setSize; ++i) {
            crowding->addMember(temp->data);
            temp = temp->link;
        }
        temp = R.first->link;
        for (int j = 0; j < R.setSize; ++j) {
            crowding->addMember(temp->data);
            temp = temp->link;
        }
    }
    return *crowding;
}

template <class T>
LinkedSet<T>& LinkedSet<T>::operator-(LinkedSet<T> &R) {
    if (R.setSize == 0) return *this;
    SetNode<T>* tempR = R.first->link;
    for (int i = 0; i < R.setSize; ++i) {
        delMember(tempR->data);
        tempR = tempR->link;
    }
    return *this;
}

template <class T>
SetNode<T> *LinkedSet<T>::getFirst() const {
    return first;
}

template <class T>
SetNode<T> *LinkedSet<T>::getLast() const {
    return last;
}

template <class T>
bool LinkedSet<T>::operator==(LinkedSet<T> &R) {
    if (setSize != R.setSize) return false;
    else {
        SetNode<T> *temp = first, *tempR = first;
        for (int i = 0; i < setSize; ++i) {
            temp = temp->link;
            tempR = tempR->link;
            if (temp->data != tempR->data){
                return false;
            }
        }
    }
    return true;
}

template <class T>
bool LinkedSet<T>::subSet(LinkedSet<T> &R) {
    if (R.setSize > setSize){
        return false;
    }else if(R.setSize == 0){
        return true;
    }
    SetNode<T> *temp = first->link, *tempR = R.first->link;
    if (tempR->data < temp->data || R.last->data > last->data){
        return false;
    }
    while (temp != last && tempR != R.last){
        if (tempR->data < temp->data){
            return false;
        }
        if (tempR->data == temp->data) {
            tempR = tempR->link;
            continue;
        }
        temp = temp->link;
    }
    return true;
}

#endif //SET_LINKEDSET_H
