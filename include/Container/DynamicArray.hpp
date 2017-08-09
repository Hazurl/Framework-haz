#ifndef __HAZ_DYNAMIC_ARRAY
#define __HAZ_DYNAMIC_ARRAY

#include <Tools/Macro.hpp>
#include <Tools/Utility.hpp>

#include <iostream>
#include <initializer_list>

BEG_NAMESPACE_HAZ

template<typename T>
class DynamicArray {
public:
    typedef             T  Value;
    typedef       const T  ValueConst;
    typedef             T& ValueRef;
    typedef       const T& ValueConstRef;
    typedef             T* ValuePtr;
    typedef       const T* ValueConstPtr;
    
    typedef      ValuePtr  iterator;
    typedef ValueConstPtr  iterator_const;

    DynamicArray() : 
        data(nullptr),
        size(0), 
        capacity(capacity_start) 
    {
    }

    DynamicArray(const DynamicArray& other) : 
        data(other.size > 0 ? new T[other.capacity] : nullptr), 
        size(other.size), 
        capacity(other.size > 0 ? other.capacity : capacity_start) 
    {
        if (other.size > 0)
            arrayCopy<T>(other.data, data, other.size); 
    }

    ~DynamicArray() {
        if (size > 0)
            delete [] data;
    }

    DynamicArray(DynamicArray&& other) : 
        data(other.data), 
        size(other.size), 
        capacity(other.capacity) 
    {
        other.data = nullptr;
    }

    inline DynamicArray& operator=(DynamicArray other) {
        DynamicArray::swap(*this, other);
        return *this;
    }

    static void swap (DynamicArray& a, DynamicArray& b) {
        haz::swap(a.size, b.size);
        haz::swap(a.capacity, b.capacity);
        haz::swap(a.data, b.data);
    }

    inline iterator begin() {
        return data;
    }

    inline iterator end() {
        return data + size;
    }
    
    inline iterator_const begin() const {
        return data;
    }

    inline iterator_const end() const {
        return data + size;
    }
    
    void push(const std::initializer_list<T>& list) {
        if (size + list.size() > capacity)
            reserve(size + list.size());
        
        if (data == nullptr)
            data = new T[capacity];

        for (const T& t : list)
            data[size++] = t;
    }

    void push(T v) {
        if (size + 1 > capacity)
            reserve();

        if (data == nullptr)
            data = new T[capacity];

        data[size++] = v;
    }

    Value pop_back () {
        HAZ_ASSERT_MSG("Out of bounds !", size > 0)
        return data[--size];
    }

    Value pop(unsigned int pos) {
        HAZ_ASSERT_MSG("Out of bounds !", pos >= 0 && pos < size && data != nullptr);

        T out = data[pos];
        remove(pos);

        return out;
    }

    void remove(unsigned int pos) {
        HAZ_ASSERT_MSG("Out of bounds !", pos >= 0 && pos < size && data != nullptr);
        arrayCopy<int>(data + pos + 1, data + pos, size - pos - 1);
        --size;
    }

    void insert(unsigned int pos, T v) {
        HAZ_ASSERT_MSG("Out of bounds !", pos >= 0 && pos < size);
        if (size + 1 > capacity)
            reserve();

        if (data == nullptr)
            data = new T[capacity];
        
        arrayCopyR<int>(data + size - 1, data + size, size - pos);
        data[pos] = v;
        ++size;
    }

    ValueRef operator[] (unsigned int pos) {
        HAZ_ASSERT_MSG("Out of bounds !", pos >= 0 && pos < size && data != nullptr);
        return data[pos];
    }

    inline ValueConstRef operator[] (unsigned int pos) const {
        HAZ_ASSERT_MSG("Out of bounds !", pos >= 0 && pos < size && data != nullptr);
        return data[pos];
    }

    void reserve(unsigned int new_cap) {
        if (data != nullptr) {
            T* new_data = new T[new_cap];
            arrayCopy<int>(data, new_data, haz::min(capacity, new_cap));
            delete[] data;
            data = new_data;
        }
        capacity = new_cap;
        size = haz::min(capacity, size);
    }

    void resize(unsigned int new_size, T value = T()) {
        if (size < new_size) {
            if (capacity < new_size)
                reserve(new_size);

            if (data == nullptr)
                data = new T[capacity];

            for (unsigned int i = size; i < new_size; ++i)
                data[i] = value;
        }

        size = new_size;
    }

    inline void cut() {
        reserve(size);
    }

    inline bool isEmpty() const { 
        return size == 0;
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

    inline void reserve() {
        reserve(capacity * 2);
    }
};

END_NAMESPACE_HAZ

#endif