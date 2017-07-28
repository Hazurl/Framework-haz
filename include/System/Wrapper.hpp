#ifndef __SYSTEM_WRAPPER
#define __SYSTEM_WRAPPER

#include <System/Object.hpp>
#include <sstream>

BEG_NAMESPACE_HAZ

template <typename T>
class Wrapper : public Object {
public:
    typedef       T         type;
    typedef const T         constant;
    typedef       T*        pointer;
    typedef const T*        const_pointer;
    typedef       T&        reference;
    typedef const T&        const_reference;

    inline Wrapper<T>(T v = Wrapper<T>::default_value) : value(v) {}
    inline ~Wrapper() {};
    inline Wrapper(Wrapper const& base) : value(base.value) {}
    
            inline              operator T  ()    const  { return value;                            }
            inline T&           get         ()           { return value;                            }
            inline T const&     get         ()    const  { return value;                            }

            inline Wrapper<T>&  operator =  (T v)        { value = v;  return *this;                }

            inline Wrapper<T>&  operator += (T v)        { value += v; return *this;                }
            inline Wrapper<T>&  operator -= (T v)        { value -= v; return *this;                }
            inline Wrapper<T>&  operator *= (T v)        { value *= v; return *this;                }
            inline Wrapper<T>&  operator /= (T v)        { value /= v; return *this;                }
            inline Wrapper<T>&  operator %= (T v)        { value %= v; return *this;                }

            inline Wrapper<T>&  operator &= (T v)        { value &= v; return *this;                }
            inline Wrapper<T>&  operator |= (T v)        { value |= v; return *this;                }
            inline Wrapper<T>&  operator ^= (T v)        { value ^= v; return *this;                }
            inline Wrapper<T>&  operator <<=(T v)        { value <<= v;return *this;                }
            inline Wrapper<T>&  operator >>=(T v)        { value >>= v;return *this;                }

            inline Wrapper<T>&  operator ++ ()           { ++value;    return *this;                }
            inline Wrapper<T>   operator ++ (int)        { return Wrapper<T>(value++);              }
            inline Wrapper<T>&  operator -- ()           { --value;    return *this;                }
            inline Wrapper<T>   operator -- (int)        { return Wrapper<T>(value--);              }

            inline bool         operator == (T v) const  { return value == v;                       }
            inline bool         operator != (T v) const  { return !(value == v);                    }
            inline bool         operator <  (T v) const  { return value < v;                        }
            inline bool         operator >  (T v) const  { return value > v;                        }
            inline bool         operator <= (T v) const  { return !(value > v);                     }
            inline bool         operator >= (T v) const  { return !(value < v);                     }

            inline Wrapper<T>   operator +  ()           { return Wrapper<T>(+value);               }
            inline Wrapper<T>   operator -  ()           { return Wrapper<T>(-value);               }
            inline Wrapper<T>   operator !  ()           { return Wrapper<T>(!value);               }
            inline Wrapper<T>   operator ~  ()           { return Wrapper<T>(~value);               }

    friend  inline Wrapper<T>   operator +  (Wrapper<T> w, Wrapper<T> v) { return w += v;           }
    friend  inline Wrapper<T>   operator +  (T w, Wrapper<T> v)          { return w += v;           }
    friend  inline Wrapper<T>   operator +  (Wrapper<T> w, T v)          { return w += v;           }

    friend  inline Wrapper<T>   operator -  (Wrapper<T> w, Wrapper<T> v) { return w -= v;           }
    friend  inline Wrapper<T>   operator -  (T w, Wrapper<T> v)          { return w -= v;           }
    friend  inline Wrapper<T>   operator -  (Wrapper<T> w, T v)          { return w -= v;           }

    friend  inline Wrapper<T>   operator *  (Wrapper<T> w, Wrapper<T> v) { return w *= v;           }
    friend  inline Wrapper<T>   operator *  (T w, Wrapper<T> v)          { return w *= v;           }
    friend  inline Wrapper<T>   operator *  (Wrapper<T> w, T v)          { return w *= v;           }

    friend  inline Wrapper<T>   operator /  (Wrapper<T> w, Wrapper<T> v) { return w /= v;           }
    friend  inline Wrapper<T>   operator /  (T w, Wrapper<T> v)          { return w /= v;           }
    friend  inline Wrapper<T>   operator /  (Wrapper<T> w, T v)          { return w /= v;           }

    friend  inline Wrapper<T>   operator %  (Wrapper<T> w, Wrapper<T> v) { return w %= v;           }
    friend  inline Wrapper<T>   operator %  (T w, Wrapper<T> v)          { return w %= v;           }
    friend  inline Wrapper<T>   operator %  (Wrapper<T> w, T v)          { return w %= v;           }

    friend  inline Wrapper<T>   operator &  (Wrapper<T> w, Wrapper<T> v) { return w &= v;           }
    friend  inline Wrapper<T>   operator &  (T w, Wrapper<T> v)          { return w &= v;           }
    friend  inline Wrapper<T>   operator &  (Wrapper<T> w, T v)          { return w &= v;           }

    friend  inline Wrapper<T>   operator |  (Wrapper<T> w, Wrapper<T> v) { return w |= v;           }
    friend  inline Wrapper<T>   operator |  (T w, Wrapper<T> v)          { return w |= v;           }
    friend  inline Wrapper<T>   operator |  (Wrapper<T> w, T v)          { return w |= v;           }

    friend  inline Wrapper<T>   operator ^  (Wrapper<T> w, Wrapper<T> v) { return w ^= v;           }
    friend  inline Wrapper<T>   operator ^  (T w, Wrapper<T> v)          { return w ^= v;           }
    friend  inline Wrapper<T>   operator ^  (Wrapper<T> w, T v)          { return w ^= v;           }

    friend  inline Wrapper<T>   operator <<  (Wrapper<T> w, Wrapper<T> v) { return w <<= v;           }
    friend  inline Wrapper<T>   operator <<  (T w, Wrapper<T> v)          { return w <<= v;           }
    friend  inline Wrapper<T>   operator <<  (Wrapper<T> w, T v)          { return w <<= v;           }

    friend  inline Wrapper<T>   operator >>  (Wrapper<T> w, Wrapper<T> v) { return w >>= v;           }
    friend  inline Wrapper<T>   operator >>  (T w, Wrapper<T> v)          { return w >>= v;           }
    friend  inline Wrapper<T>   operator >>  (Wrapper<T> w, T v)          { return w >>= v;           }

    // Objects
    inline Object::TString to_string() const;
    inline int hash() const;

private:
    T value;
    static const T default_value;
};

#define MAKE_BASIC_TYPE_WRAPPER(name, def_value, type...) \
typedef Wrapper<type> name;\
template<>\
const type name::default_value = def_value;\
template<>\
Object::TString name::to_string() const {\
    return std::to_string(value);\
}\
template<>\
int name::hash() const {\
    return value;\
}

MAKE_BASIC_TYPE_WRAPPER(Char, 0, char)
MAKE_BASIC_TYPE_WRAPPER(UChar, 0, unsigned char)

MAKE_BASIC_TYPE_WRAPPER(WChar, 0, wchar_t)

MAKE_BASIC_TYPE_WRAPPER(Int, 0, int)
MAKE_BASIC_TYPE_WRAPPER(UInt, 0, unsigned int)

MAKE_BASIC_TYPE_WRAPPER(Short, 0, short)
MAKE_BASIC_TYPE_WRAPPER(UShort, 0, unsigned short)

MAKE_BASIC_TYPE_WRAPPER(Long, 0, long)
MAKE_BASIC_TYPE_WRAPPER(ULong, 0, unsigned long)

MAKE_BASIC_TYPE_WRAPPER(LLong, 0, long long)
MAKE_BASIC_TYPE_WRAPPER(ULLong, 0, unsigned long long)

MAKE_BASIC_TYPE_WRAPPER(Float, 0, float)

MAKE_BASIC_TYPE_WRAPPER(Double, 0, double)
MAKE_BASIC_TYPE_WRAPPER(LDouble, 0, long double)

MAKE_BASIC_TYPE_WRAPPER(Bool, false, bool)

#undef MAKE_BASIC_TYPE_WRAPPER

template<typename T>
const T Wrapper<T>::default_value = T();
template<typename T>
Object::TString Wrapper<T>::to_string() const { std::ostringstream os; os << value; return os.str(); }
template<typename T>
int Wrapper<T>::hash() const { return (int)value; }

END_NAMESPACE_HAZ

#endif