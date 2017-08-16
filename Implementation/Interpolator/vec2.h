#ifndef VEC2_H
#define VEC2_H

#include <initializer_list>

class Vec2
{
public:
    int x;
    int y;
    Vec2(int new_x = 0, int new_y = 0);
    Vec2(const std::initializer_list<int>& init_list);
    Vec2(const Vec2& new_vec2);
    Vec2& operator=(const Vec2& new_vec2);
    Vec2& operator=(const std::initializer_list<int>& init_list);
    Vec2 operator+(const Vec2& rhs);
};

#endif // VEC2_H
