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
    uintptr_t listBase;
    size_t offsetLength;
    size_t offsetHead;
    size_t offsetTail;
    size_t offsetPrev;
    size_t offsetNext;
    bool hasTail;

    LinkedList(uintptr_t base, size_t lenOff, size_t headOff, size_t tailOff,
        size_t prevOff, size_t nextOff)
        : listBase(base), offsetLength(lenOff), offsetHead(headOff),
        offsetTail(tailOff), offsetPrev(prevOff), offsetNext(nextOff), hasTail(true) {}

    // Overload: tail omitted
    LinkedList(uintptr_t base, size_t lenOff, size_t headOff,
        size_t prevOff, size_t nextOff)
        : listBase(base), offsetLength(lenOff), offsetHead(headOff), offsetTail(0),
        offsetPrev(prevOff), offsetNext(nextOff), hasTail(false) {}

    int getLength() const {
        return *(int*)(listBase + offsetLength);
    }

    LinkedListNode<StructType> getHead() const {
        uintptr_t head = *(uintptr_t*)(listBase + offsetHead);
        return LinkedListNode<StructType>(head, offsetPrev, offsetNext);
    }

    LinkedListNode<StructType> getTail() const {
        if (!hasTail)
            return LinkedListNode<StructType>(0, offsetPrev, offsetNext); // invalid node
        uintptr_t tail = *(uintptr_t*)(listBase + offsetTail);
        return LinkedListNode<StructType>(tail, offsetPrev, offsetNext);
    }

    void forEach(std::function<void(const StructType&)> callback) const {
        for (auto node = getHead(); node.isValid(); node = node.getNext()) {
            callback(node.getData());
        }
    }
};