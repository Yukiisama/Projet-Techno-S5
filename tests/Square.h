#ifndef SQUARE_H
#define SQUARE_H
#include "ei_types.h"
#include "Point.h"
#include "hw_interface.h"
#include "Shape.h"

class Square : public Shape{

public:
    //Constructors
    Square(ei_size_t size);
    Square(ei_size_t size , Point pt);
    Square(ei_size_t size, unsigned int x , unsigned int y);
    ~Square();

    int getTopLeft_x() const;

    int getTopLeft_y() const;


    Point getTopLeft() const;


    ei_size_t getSize();
        
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
    Point _top_left;  ///< Coordinates of the top-left corner of the square.
    Point _point_speed;
    ei_size_t _size;       ///< Size of the square.


};
#endif
