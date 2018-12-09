#include "Point.h"
#include "Rectangle.h"
#include "ei_draw.h"

#include <string>
#include <iostream>

   
    Rectangle::Rectangle(ei_size_t size): 
        _size(size)
        {
        //_top_left= Point(); Pas besoin de l'appeler car contructeur par défaut sera appelé
        }
    Rectangle::Rectangle(ei_size_t size , Point pt):
        _size(size) {
            _top_left = Point(pt);
            
        }
    
    Rectangle::Rectangle(ei_size_t size, unsigned int x , unsigned int y):
    _size(size)
    {
        _top_left.setX(x);
        _top_left.setY(y);
    }

    int Rectangle::getTopLeft_x() const {
        return _top_left.getX();
    }


    int Rectangle::getTopLeft_y() const {
        return _top_left.getY();
    }


    Point Rectangle::getTopLeft() const {
        return _top_left;
    }


    ei_size_t Rectangle::getSize() const {
        return _size;
    }

    int Rectangle::getwidth() const {
        return _size.width;
    }

    int Rectangle::getheight() const {
        return _size.height;
    }

    void Rectangle::setheight( int height){
        _size.height = height;
    }

    void Rectangle::setwidth( int width){
        _size.width = width;
    }

    void Rectangle::set_pt_x( int x){
        _top_left.setX(x);
    }


    void Rectangle::set_pt_y( int y){
        _top_left.setY(y);
    }
    Rectangle::~Rectangle(){}

    void Rectangle::draw(ei_surface_t surface, ei_surface_t r){ 
        ei_point_t r_point;
        r_point.x = _top_left.getX();
        r_point.y = _top_left.getY();
        ei_copy_surface(surface, r, &r_point, EI_TRUE);
        hw_surface_unlock(r);
        hw_surface_free(r);
    }
    void Rectangle::setPosition(const Point &v){
        _top_left.setX(v.getX());
        _top_left.setY(v.getY());
    }
    void Rectangle::setPosition(float x , float y){
        _top_left.setX((int)x);
        _top_left.setY((int)y);
    }

    void Rectangle::setSpeed(const Point &speed){
        _point_speed.setX(speed.getX());
        _point_speed.setY(speed.getY());
    }
    Point Rectangle::getSpeed()const{
        return _point_speed;
    }


        


