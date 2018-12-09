#ifndef POINT_H
#define POINT_H
#include "ei_types.h"
#include "hw_interface.h"
#include  <iostream>
class Point{
    
    public:
    //Point();
    Point(int x = 0 , int y = 0);
    Point(const int x_y);
    ~Point();
    int getX() const;
    int getY() const;
    void setX(int x) ;
    void setY(int y) ;
    void draw(ei_surface_t surface, ei_surface_t r);
    Point operator+(const Point &b);
    Point operator-(const Point &b);
    friend std::ostream& operator << (std::ostream&,Point& p);
    
    
    
    private:
    int _x;  ///< The abscissa of the point. The origin is on the left side of the image.
    int _y;  ///< The ordinate of the point, the origin is at the top of the image,
};
#endif