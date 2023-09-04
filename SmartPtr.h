#pragma once

#include <cstddef>
#include <stdexcept>

template<typename T>
class SmartPtr {
public:
    explicit SmartPtr(T* object) {
        if (!object) throw std::runtime_error("SmartPtr to nullptr");
        this->object = object;
        this->counter = new size_t(1);
    }

    ~SmartPtr() {
        --*counter;
        if (*counter == 0) {
            delete object;
            delete counter;
        }
    }

    SmartPtr(SmartPtr<T> &other) {
        if (!object) throw std::runtime_error("SmartPtr to nullptr");
        this->object = other.object;
        this->counter = other.counter;
        ++*counter;
    }

    T& operator*() {
        return *object;
    }

    T& operator->() {
        return *object;
    }

    explicit operator bool() const {
        return object != nullptr;
    }

    T& get() const {
        return *object;
    }

    [[nodiscard]] size_t useCount() const {
        return *counter;
    }

private:
    T* object;
    size_t* counter;
};