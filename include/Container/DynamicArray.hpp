#include <SystemMacro.h>
#include <System/Object.hpp>

#include <iostream>

BEG_NAMESPACE_HAZ

template<typename T>
class DynamicArray : public Object {
    //HAZ_TEMPLATE_MUST_BE_BASE_OF(Object, T)
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

    int hash() const {
        return 0;
    }

    T& push(T v) {
        ++_size;
        check_resize();

        return _data[_size - 1] = v;
    }

    T remove(unsigned long pos) {
        HAZ_ASSERT_MSG("Out of bounds !", pos >= 0 && pos < _size);

        T out = _data[pos];
        for (unsigned long i = pos + 1; i < _size; ++i) {
            _data[i - 1] = _data[i];
        }
        --_size;

        return out;
    }

    unsigned long size () const {
        return _size;
    }

    unsigned long capacity () const {
        return _capacity;
    }

private:
    T* _data = nullptr;
    unsigned long _size;
    unsigned long _capacity;
    static const unsigned long capacity_start = 8;

    bool check_resize() {
        if (_size <= _capacity)
            return false;

        T* new_data = new T[_capacity * 2];
        T* cur = new_data;
        T* old = _data;
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
