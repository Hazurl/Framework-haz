#ifndef __HAZ_GEOM2_VECTOR
#define __HAZ_GEOM2_VECTOR

#include <Macro.hpp>
#include <cmath>

BEG_NAMESPACE_HAZ_GEOM2

template<typename T>
struct Coords {
    Coords(T x, T y) : x(x), y(y) {};
    Coords() {};
    T x, y;
};

template<typename T>
class Vector : private Coords<T> {
public:

    Vector() : Coords<T>() {}
    Vector(T x, T y) : Coords<T>(x, y) {}

    static Vector<T> up()      { static_assert(!std::is_unsigned<T>::value, "Must be unsigned"); return {0, 1};  }
    static Vector<T> down()    { static_assert(!std::is_unsigned<T>::value, "Must be unsigned"); return {0, -1}; }
    static Vector<T> left()    { static_assert(!std::is_unsigned<T>::value, "Must be unsigned"); return {-1, 0}; }
    static Vector<T> right()   { static_assert(!std::is_unsigned<T>::value, "Must be unsigned"); return {1, 0};  }

    ~Vector() {}

    inline T getX() const { return this->x; }
    inline T getY() const { return this->y; }
    inline void setX(T _x) { this->x = _x; }
    inline void setY(T _y) { this->y = _y; }

    inline double magnitude2() const {
        return this->x * this->x + this->y * this->y;
    }

    inline double magnitude() const {
        return std::sqrt(magnitude2());
    }

    Vector<T> normalize() const {
        double l = magnitude();
        return { this->x / l, this->y / l };
    }

    Vector<T> abs() const {
        return { haz::abs(this->x), haz::abs(this->y) };
    }

    Vector<T> clamp(Vector<T> const& a, Vector<T> const& b) {
        return { haz::clamp<T>(this->x, a.x, b.x), haz::clamp<T>(this->y, a.y, b.y) };
    }

    static Vector<T> lerp(double t, Vector<T> const& a, Vector<T> const& b) {
        return { haz::lerp<T>(t, a.x, b.x), haz::lerp<T>(t, a.y, b.y) };
    }

    static Vector<T> lerpClamp(double t, Vector<T> const& a, Vector<T> const& b) {
        return { haz::lerpClamp<T>(t, a.x, b.x), haz::lerpClamp<T>(t, a.y, b.y) };
    }

    static Vector<T> const& min(Vector<T> const& a, Vector<T> const& b) {
        return { haz::min<T>(a.x, b.x), haz::min<T>(a.y, b.y) };
    }

    static Vector<T> const& max(Vector<T> const& a, Vector<T> const& b) {
        return { haz::max<T>(a.x, b.x), haz::max<T>(a.y, b.y) };
    }

    T dot(Vector<T> const& a) const {
        return a.x * this->x + a.y * this->y;
    }

    T operator [] (unsigned int pos) {
        HAZ_ASSERT(pos == 0 || pos == 1);
        return pos == 0 ? this->x : this->y;
    }

    Vector<T>& operator += (Vector<T> const& v) { this->x += v.x; this->y += v.y; return *this; }
    Vector<T>& operator -= (Vector<T> const& v) { this->x -= v.x; this->y -= v.y; return *this; }
    Vector<T>& operator *= (T f) { this->x *= f; this->y *= f; return *this; }
    Vector<T>& operator /= (T f) { this->x /= f; this->y /= f; return *this; }
    Vector<T>& operator %= (T f) { this->x %= f; this->y %= f; return *this; }
    bool operator == (Vector<T> const& v) const { return this->x == v.x && this->y == v.y; } 
    bool operator != (Vector<T> const& v) const { return !(*this == v); } 
    bool operator <  (Vector<T> const& v) const { return magnitude2() < v.magnitude2(); } 
    bool operator >  (Vector<T> const& v) const { return magnitude2() > v.magnitude2(); } 
    bool operator <= (Vector<T> const& v) const { return !(*this > v); } 
    bool operator >= (Vector<T> const& v) const { return !(*this < v); } 

    Vector<T> operator + () { return Vector<T>(+this->x, +this->y); } 
    Vector<T> operator - () { return Vector<T>(-this->x, -this->y); } 

    friend Vector<T> operator + (Vector<T> a, Vector<T> const& b) { return a += b; }
    friend Vector<T> operator - (Vector<T> a, Vector<T> const& b) { return a -= b; }
    friend Vector<T> operator * (Vector<T> a, T f) { return a *= f; }
    friend Vector<T> operator / (Vector<T> a, T f) { return a /= f; }
    friend Vector<T> operator % (Vector<T> a, T f) { return a %= f; }

    friend std::ostream& operator <<(std::ostream& os, Vector<T> const& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }

    friend std::istream& operator <<(std::istream& is, Vector<T>& v) {
        is >> v.x;
        is >> v.y;
        return is;
    }

};

END_NAMESPACE_HAZ_GEOM2

#endif
