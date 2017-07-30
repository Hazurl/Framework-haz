#include <Macro.h>
#include <Utility.h>

#include <iostream>

BEG_NAMESPACE_HAZ

template<typename T>
class DynamicArray {
public:
    DynamicArray() : 
        data(new T[capacity_start]), 
        size(0), 
        capacity(capacity_start) 
    {
    }

    DynamicArray(const DynamicArray& other) : 
        data(new T[other.capacity]), 
        size(other.size), 
        capacity(other.capacity) 
    {
        arrayCopy<T>(other.data, data, other.size); 
    }

    ~DynamicArray() {
        SAFE_DELETE_ARR(data)
    }

    DynamicArray(DynamicArray&& other) : 
        data(other.data), 
        size(other.size), 
        capacity(other.capacity) 
    {
        other.data = nullptr;
    }

    inline DynamicArray& operator=(DynamicArray other) {
        haz::swap(data, other.data);
        return *this;
    }

    T& push(T v) {
        if (++size > capacity)
            resize();

        return data[size - 1] = v;
    }

    T pop(unsigned int pos) {
        HAZ_ASSERT_MSG("Out of bounds !", pos >= 0 && pos < size && data != nullptr);

        T out = data[pos];
        arrayCopy<int>(data + pos + 1, data + pos, size - pos - 1);
        --size;

        return out;
    }

    void remove(unsigned int pos) {
        HAZ_ASSERT_MSG("Out of bounds !", pos >= 0 && pos < size && data != nullptr);
        arrayCopy<int>(data + pos + 1, data + pos, size - pos - 1);
        --size;
    }

    T& operator[] (unsigned int pos) {
        HAZ_ASSERT_MSG("Out of bounds !", pos >= 0 && pos < size && data != nullptr);
        return data[pos];
    }

    inline const T& operator[] (unsigned int pos) const {
        HAZ_ASSERT_MSG("Out of bounds !", pos >= 0 && pos < size && data != nullptr);
        return data[pos];
    }

    inline unsigned int getSize () const {
        return size;
    }

    inline unsigned int getCapacity () const {
        return capacity;
    }

private:
    T* data = nullptr;
    unsigned int size;
    unsigned int capacity;
    static const unsigned int capacity_start = 8;

    void resize() {
        T* newdata = new T[capacity * 2];
        arrayCopy<int>(data, newdata, capacity);

        delete[] data;
        data = newdata;
        capacity *= 2;
    }
};


END_NAMESPACE_HAZ
