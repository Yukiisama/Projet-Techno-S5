#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "ei_types.h"
#include "Point.h"
#include "hw_interface.h"
#include "Shape.h"

class Rectangle : public Shape{

public:
    //Constructors
    Rectangle(ei_size_t size);
    Rectangle(ei_size_t size , Point pt);
    Rectangle(ei_size_t size, unsigned int x , unsigned int y);
    ~Rectangle();

    int getTopLeft_x() const;

    int getTopLeft_y() const;


    Point getTopLeft() const;


    ei_size_t getSize() const;
        
    int getwidth() const;

    int getheight() const;

    void setheight( int height);

    void setwidth( int width);

    void set_pt_x( int x);
    void draw(ei_surface_t surface, ei_surface_t r);
    void setPosition(const Point &v);
    void setPosition(float x , float y);
    void set_pt_y( int y);
    void setSpeed(const Point &speed);
    Point getSpeed()const;
    


private: 
    Point _top_left;  ///< Coordinates of the top-left corner of the rectangle.
    Point _point_speed;
    ei_size_t _size;       ///< Size of the rectangle.


};
#endif
