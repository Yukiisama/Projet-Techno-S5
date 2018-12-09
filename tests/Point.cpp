#include "Point.h"
#include "ei_draw.h"

#include <string>
#include <iostream>

   
    //Point::Point(): 
      //  _x(0),_y(0){}
    Point::Point(int x, int y): 
        _x(x),_y(y){}
    Point::Point(const int x_y): 
        _x(x_y),_y(x_y){}
    
    
    int Point::getX() const{
        return _x;
    }
    int Point::getY() const{
        return _y;
    }   
    void Point::setX(int x){
        _x=x;
    }
    void Point::setY(int y){
        _y=y;
    }
    Point::~Point(){}
    Point Point::operator+(const Point &b){
        Point p = Point();
        p.setX(_x+b.getX());
        p.setY(_y+b.getY());
        return p;
    }
    Point Point::operator-(const Point &b){
        Point p = Point();
        p.setX(_x-b.getX());
        p.setY(_y-b.getY());
        return p;
    }
    std::ostream& operator << (std::ostream &f,Point &p){

        f<<"["<<p.getX()<<","<<p.getY()<<"]";
        return f;
    }