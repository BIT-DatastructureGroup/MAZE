#pragma once
#include "MyQueue.h"
template <typename T>
class MyStack {
    Node<T>* stackHead;
public:
    MyStack() {
        stackHead = 0;
    }
    ~MyStack() {
        while (!Empty()) Pop();
    }
    void Push(T elem) {
        Node<T>* newNode = new Node<T>(elem);
        if (stackHead) {
            stackHead->next = newNode;
            newNode->prev = stackHead;
            stackHead = newNode;
        }
        else {
            stackHead = newNode;
            newNode->prev = 0;
        }
    }
    T Top() {
        if (stackHead) {
            return stackHead->data;
        }
        else {
            throw "Empty Queue, Do not call Top()!";
        }
    }
    bool Empty() {
        return stackHead == 0;
    }
    void Pop() {
        if (stackHead == 0) {
            throw "Empty Stack, Do not call Pop()!";
        }
        Node<T>* tmpPrev = stackHead->prev;
        delete stackHead;
        stackHead = tmpPrev;
    }
};