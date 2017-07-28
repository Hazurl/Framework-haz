#include <SystemMacro.h>
#include <System/Object.hpp>

#include <iostream>

BEG_NAMESPACE_HAZ

template<typename T>
class DynamicArray : public Object {
public:
    DynamicArray<T>() : _data(new T[capacity_start]), _size(0), _capacity(capacity_start) {}

    ~DynamicArray() {
        SAFE_DELETE_ARR(_data)
    }

    DynamicArray(DynamicArray const& other) {
        SAFE_DELETE_ARR(_data)
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;
    }

    // Object Implementation
    Object::TString to_string () const {
        Object::TString str = "{";
        for (unsigned long i = 0; i < _size; ++i) {
            if (i > 0) str += ", ";
            str += value_to_string(_data[i]);
        }
        return str + "}";
    }

    void push(T v) {
        ++_size;
        check_resize();

        _data[_size - 1] = v;
    }

    unsigned long size () const {
        return _size;
    }

    unsigned long capacity () const {
        return _capacity;
    }

private:
    typename T::pointer _data = nullptr;
    unsigned long _size;
    unsigned long _capacity;
    static const unsigned long capacity_start = 8;

    bool check_resize() {
        if (_size <= _capacity)
            return false;

        typename T::pointer new_data = new T[_capacity * 2];
        typename T::pointer cur = new_data;
        typename T::pointer old = _data;
        for (unsigned long i = 0; i < _capacity; ++i, ++cur, ++old)
            *cur = *old;

        SAFE_DELETE_ARR(_data)
        _data = new_data;
        _capacity *= 2;

        return true;
    }

    Object::TString value_to_string (typename std::remove_pointer<T>::type* v) const { return v->to_string(); }
    Object::TString value_to_string (typename std::remove_pointer<T>::type  v) const { return v.to_string();  }
};


END_NAMESPACE_HAZ
