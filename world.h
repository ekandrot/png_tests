//
//  world.hpp
//  
//
//  Created by reed on 9/23/15.
//
//

#ifndef world_h
#define world_h

#include <stdio.h>
#include <math.h>
#include <vector>

#define sqr(x) ((x) * (x))

struct color4 {
    color4() : r(0), g(0), b(0), a(1) {}
    color4(double r, double g, double b, double a) : r(r), g(g), b(b), a(a) {}
    inline color4& operator+=(const color4& rhs) {
        r+=rhs.r; g+=rhs.g; b+=rhs.b;
        return *this;
    }
    double r, g, b, a;
};
inline color4 operator+(const color4& a, const color4& b) {
    return {a.r+b.r, a.g+b.g, a.b+b.b, 1};
}
inline color4 operator*(double a, const color4& b) {
    return color4(a*b.r, a*b.g, a*b.b, 1);
}
inline color4 operator/(const color4& b, double a) {
    return (1.0/a)*b;
}


struct coord3 {
    coord3() : x(0), y(0), z(0) {}
    coord3(double x, double y, double z) : x(x), y(y), z(z) {}
    inline coord3& operator+=(const coord3& b) {
        x+=b.x; y+=b.y; z+=b.z;
        return *this;
    }
    double x, y, z;
};
inline coord3 operator-(const coord3& a, const coord3& b) {
    return {a.x-b.x, a.y-b.y, a.z-b.z};
}
inline coord3 operator+(const coord3& a, const coord3& b) {
    return {a.x+b.x, a.y+b.y, a.z+b.z};
}
inline coord3 operator*(double a, const coord3& b) {
    return {a*b.x, a*b.y, a*b.z};
}
inline coord3 operator/(const coord3& b, double a) {
    return (1.0/a)*b;
}
inline double dot(const coord3& a, const coord3& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
inline coord3 unit_vector(const coord3& a) {
    double norm = sqrt(dot(a, a));
    return a/norm;
}


struct ray3 {
    coord3 origin;
    coord3 direction;
};


struct sphere {
    coord3 center;
    double r;
    color4 color;
};


struct world {
    void add_sphere(coord3 center, double r, color4 c);
    color4 cast_ray(const ray3& ray __attribute__((unused)));
    
private:
    std::vector<sphere> objs;
};

#endif /* world_hpp */
