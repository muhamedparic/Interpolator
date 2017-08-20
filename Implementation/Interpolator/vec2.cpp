#include <stdexcept>

#include "vec2.h"

Vec2::Vec2(int new_x, int new_y)
{
    x = new_x;
    y = new_y;
}

Vec2::Vec2(const std::initializer_list<int>& init_list)
{
    if (init_list.size() != 2)
        throw std::domain_error("Can't create a vec2 with an initializer_list of size != 2");
    x = *init_list.begin();
    y = *(init_list.begin() + 1);
}

Vec2::Vec2(const Vec2 &new_vec2)
    : Vec2(new_vec2.x, new_vec2.y)
{

}

Vec2& Vec2::operator=(const Vec2& new_vec2)
{
    x = new_vec2.x;
    y = new_vec2.y;
    return *this;
}

Vec2& Vec2::operator=(const std::initializer_list<int>& init_list)
{
    if (init_list.size() != 2)
        throw std::domain_error("Can't create a vec2 with an initializer_list of size != 2");
    x = *init_list.begin();
    y = *(init_list.begin() + 1);
    return *this;
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

bool Vec2::operator==(const Vec2& rhs) const
{
    return x == rhs.x && y == rhs.y;
}

bool Vec2::operator!=(const Vec2& rhs) const
{
    return !(*this == rhs);
}
