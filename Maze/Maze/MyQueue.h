#pragma once

template <typename T>
class Node {
public:
  T data;
  Node* next;
  Node* prev;
  Node() {
    next = 0;
    prev = 0;
    T = T();
  }
  Node(T _data) {
    next = 0;
    prev = 0;
    data = _data;
  }
};


template <typename T>
class MyQueue {
  Node<T>* queueHead, * queueTail;
public:
  MyQueue() {
    queueHead = queueTail = 0;
  }
  void Push(T elem) {
    Node<T>* newNode = new Node<T>(elem);
    if (queueTail) {
      queueTail->next = newNode;
      queueTail = newNode;
    }
    else {
      queueHead = newNode;
      queueTail = newNode;
    }
  }
  T Front() {
    if (queueHead) {
      return queueHead->data;
    }
    else {
      throw "Empty Queue, Do not call Top()!";
    }
  }
  bool Empty() {
    return queueHead == 0;
  }
  void Pop() {
    if (queueHead == 0) {
      throw "Empty Queue, Do not call Pop()!";
    }
    // 只有一个元素的时候
    if (queueHead == queueTail) {
      delete queueHead;
      queueHead = queueTail = 0;
      return;
    }
    // 有多个元素，释放head，后移head指针
    Node<T>* tmpNext = queueHead->next;
    delete queueHead;
    queueHead = tmpNext;
  }
};