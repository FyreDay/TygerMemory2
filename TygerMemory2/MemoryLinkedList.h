#pragma once
#include <cstdint>
#include <iostream>
#include <functional>
#include <stdexcept>

template<typename StructType>
class LinkedListNode {
public:
    uintptr_t address;
    size_t offsetPrev;
    size_t offsetNext;

    LinkedListNode(uintptr_t addr, size_t offPrev, size_t offNext)
        : address(addr), offsetPrev(offPrev), offsetNext(offNext) {}

    bool isValid() const {
        return address != 0;
    }

    LinkedListNode getNext() const {
        uintptr_t next = *(uintptr_t*)(address + offsetNext);
        return LinkedListNode(next, offsetPrev, offsetNext);
    }

    LinkedListNode getPrev() const {
        uintptr_t prev = *(uintptr_t*)(address + offsetPrev);
        return LinkedListNode(prev, offsetPrev, offsetNext);
    }

    StructType getData() const {
        if (!isValid()) throw std::runtime_error("Attempted to get data from an invalid node");
        return StructType(address);
    }
};

template<typename StructType>
class LinkedList {
public:
    int* lengthPtr;
    uintptr_t head;
    uintptr_t tail;
    size_t offsetPrev;
    size_t offsetNext;
    bool hasTail;

    LinkedList(int* len, uintptr_t* head, uintptr_t* tail,
        size_t prevOff, size_t nextOff)
        : lengthPtr(len), head(*head), tail(*tail),
        offsetPrev(prevOff), offsetNext(nextOff), hasTail(true) {}

    // Overload: tail omitted
    LinkedList(int* len, uintptr_t head,
        size_t prevOff, size_t nextOff)
        : lengthPtr(len), head(head), tail(nullptr),
        offsetPrev(prevOff), offsetNext(nextOff), hasTail(false) {}

    int getLength() const {
        return *lengthPtr;
    }

    LinkedListNode<StructType> getHead() const {
        return LinkedListNode<StructType>(head, offsetPrev, offsetNext);
    }

    LinkedListNode<StructType> getTail() const {
        if (!hasTail || tail == nullptr)
            return LinkedListNode<StructType>(0, offsetPrev, offsetNext); // invalid node
        return LinkedListNode<StructType>(tail, offsetPrev, offsetNext);
    }

    void forEach(std::function<void(const StructType&)> callback) const {
        for (auto node = getHead(); node.isValid(); node = node.getNext()) {
            callback(node.getData());
        }
    }
};