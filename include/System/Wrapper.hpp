#ifndef __SYSTEM_WRAPPER
#define __SYSTEM_WRAPPER

#include <System/Object.hpp>
#include <sstream>

BEG_NAMESPACE_HAZ

namespace __hide {
    template <typename T>
    class Wrapper : public Object {
    public:
        typedef       T         type;
        typedef const T         constant;
        typedef       T*        pointer;
        typedef const T*        const_pointer;
        typedef       T&        reference;
        typedef const T&        const_reference;

        static const  T         default_value;

                                    inline Wrapper<T>(T v = Wrapper<T>::default_value) : value(v) {}

                                    inline ~Wrapper() {};
        template<typename X>        inline Wrapper(Wrapper<X> const& base) : value(base.value) {}
        
                                    inline              operator T  ()    const  { return value;                            }
                                    inline T&           get         ()           { return value;                            }
                                    inline T const&     get         ()    const  { return value;                            }

        template<typename X>    	inline Wrapper<T>&  operator =  (X v)        { value = v;  return *this;                }

        template<typename X>    	inline Wrapper<T>&  operator += (X v)        { value += v; return *this;                }
        template<typename X>    	inline Wrapper<T>&  operator -= (X v)        { value -= v; return *this;                }
        template<typename X>    	inline Wrapper<T>&  operator *= (X v)        { value *= v; return *this;                }
        template<typename X>    	inline Wrapper<T>&  operator /= (X v)        { value /= v; return *this;                }
        template<typename X>    	inline Wrapper<T>&  operator %= (X v)        { value %= v; return *this;                }

        template<typename X>    	inline Wrapper<T>&  operator &= (X v)        { value &= v; return *this;                }
        template<typename X>    	inline Wrapper<T>&  operator |= (X v)        { value |= v; return *this;                }
        template<typename X>    	inline Wrapper<T>&  operator ^= (X v)        { value ^= v; return *this;                }
        template<typename X>    	inline Wrapper<T>&  operator <<=(X v)        { value <<= v;return *this;                }
        template<typename X>    	inline Wrapper<T>&  operator >>=(X v)        { value >>= v;return *this;                }

                                    inline Wrapper<T>&  operator ++ ()           { ++value;    return *this;                }
                                    inline Wrapper<T>   operator ++ (int)        { return Wrapper<T>(value++);              }
                                    inline Wrapper<T>&  operator -- ()           { --value;    return *this;                }
                                    inline Wrapper<T>   operator -- (int)        { return Wrapper<T>(value--);              }

        template<typename X>    	inline bool         operator == (X v) const  { return value == v;                       }
        template<typename X>    	inline bool         operator != (X v) const  { return !(value == v);                    }
        template<typename X>    	inline bool         operator <  (X v) const  { return value < v;                        }
        template<typename X>    	inline bool         operator >  (X v) const  { return value > v;                        }
        template<typename X>    	inline bool         operator <= (X v) const  { return !(value > v);                     }
        template<typename X>    	inline bool         operator >= (X v) const  { return !(value < v);                     }

        template<typename X>    	inline bool         operator && (X v) const  { return value && v;                       }
        template<typename X>    	inline bool         operator || (X v) const  { return value || v;                       }

                
        template<typename X>    	inline Wrapper<T>&  operator ,  (X v) const  { return (value, v);                       }

                                    inline Wrapper<T>   operator +  ()           { return Wrapper<T>(+value);               }
                                    inline Wrapper<T>   operator -  ()           { return Wrapper<T>(-value);               }
                                    inline Wrapper<T>   operator !  ()           { return Wrapper<T>(!value);               }
                                    inline Wrapper<T>   operator ~  ()           { return Wrapper<T>(~value);               }

                                    inline auto&        operator *  ()           { return *value;                           }
                                    inline auto         operator -> ()           { return  value;                           }

                
        template<typename K>    	inline auto         operator [] (K k)        { return value[k];                         }
                
        template<typename K>    	inline auto         operator [] (K k) const  { return value[k];                         }
                
        template<typename ...A> 	inline auto         operator () (A... a) const { return value(a...);                    }

        #define OPERATOR(op)\
        template<typename X> friend inline auto         operator op (Wrapper<T> v, Wrapper<X> t) { return Wrapper<decltype(v.value op t.value)>(v.value op t.value);  }\
                             friend inline auto         operator op (T t, Wrapper<T> v)          { return Wrapper<decltype(t op v.value)>(t op v.value);        }\
                             friend inline auto         operator op (Wrapper<T> v,T t)           { return Wrapper<decltype(v.value op t)>(v.value op t);        }

        OPERATOR(+)
        OPERATOR(-)
        OPERATOR(*)
        OPERATOR(/)
        OPERATOR(%)
        OPERATOR(&)
        OPERATOR(|)
        OPERATOR(^)
        OPERATOR(<<)
        OPERATOR(>>)


        template<typename X> friend inline auto&         operator >> (X& x, Wrapper<T>& v)                  { return x >> v.value; }

        // Objects
                                    inline Object::TString to_string() const;
                                    inline int hash() const;

    private:
    public:
        T value;
    };

}

#define MAKE_BASIC_TYPE_WRAPPER(name, def_value, type...) \
typedef __hide::Wrapper<type> name;\
namespace __hide {\
template<>\
const type Wrapper<type>::default_value = def_value;\
template<>\
Object::TString Wrapper<type>::to_string() const {\
    return std::to_string(value);\
}\
template<>\
int __hide::Wrapper<type>::hash() const {\
    return value;\
}}

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
/*
MAKE_BASIC_TYPE_WRAPPER(Bool, false, bool)
*/
#undef MAKE_BASIC_TYPE_WRAPPER

END_NAMESPACE_HAZ

#endif