#ifndef __SYSTEM_BASICTYPE
#define __SYSTEM_BASICTYPE

#include <System/Object.hpp>
#include <sstream>

BEG_NAMESPACE_HAZ

template <typename T>
class BasicType : public Object {
public:
    inline BasicType<T>(T v = BasicType<T>::default_value) : value(v) {}
    inline ~BasicType() {};
    inline BasicType(BasicType const& base) : value(base.value) {}
    
    inline BasicType<T>& operator= (BasicType<T> base) { value = base.value;  return *this; }

    inline BasicType<T>& operator+=(BasicType<T> base) { value += base.value; return *this; }
    inline BasicType<T>& operator*=(BasicType<T> base) { value *= base.value; return *this; }
    inline BasicType<T>& operator-=(BasicType<T> base) { value -= base.value; return *this; }
    inline BasicType<T>& operator/=(BasicType<T> base) { value /= base.value; return *this; }

    inline bool operator==(BasicType<T> base) { return value == base.value;                 }
    inline bool operator!=(BasicType<T> base) { return !(value == base.value);              }
    inline bool operator< (BasicType<T> base) { return value < base.value;                  }
    inline bool operator> (BasicType<T> base) { return value > base.value;                  }
    inline bool operator<=(BasicType<T> base) { return !(value > base.value);               }
    inline bool operator>=(BasicType<T> base) { return !(value < base.value);               }

    inline operator T() const { return value; }

    // Objects
    inline Object::TString to_string() const;

private:
    T value;
    static const T default_value;
};

template<>
Object::TString BasicType<int>::to_string() const { return std::to_string(value); }
template<>
const int BasicType<int>::default_value = 0;

template<>
Object::TString BasicType<unsigned int>::to_string() const { return std::to_string(value); }
template<>
const unsigned int BasicType<unsigned int>::default_value = 0;

template<>
Object::TString BasicType<long>::to_string() const { return std::to_string(value); }
template<>
const long BasicType<long>::default_value = 0;

template<>
Object::TString BasicType<long long>::to_string() const { return std::to_string(value); }
template<>
const long long BasicType<long long>::default_value = 0;

template<>
Object::TString BasicType<unsigned long>::to_string() const { return std::to_string(value); }
template<>
const unsigned long BasicType<unsigned long>::default_value = 0;

template<>
Object::TString BasicType<unsigned long long>::to_string() const { return std::to_string(value); }
template<>
const unsigned long long BasicType<unsigned long long>::default_value = 0;

template<>
Object::TString BasicType<float>::to_string() const { return std::to_string(value); }
template<>
const float BasicType<float>::default_value = 0;

template<>
Object::TString BasicType<double>::to_string() const { return std::to_string(value); }
template<>
const double BasicType<double>::default_value = 0;

template<typename T>
Object::TString BasicType<T>::to_string() const { std::ostringstream os; os << value; return os.str(); }
template<typename T>
const T BasicType<T>::default_value = T();

END_NAMESPACE_HAZ

#endif