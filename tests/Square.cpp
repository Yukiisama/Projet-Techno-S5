#include "Point.h"
#include "Square.h"
#include "ei_draw.h"
#include "Square.h"
#include <string>
#include <iostream>


    Square::Square(ei_size_t size)
        {
		size.width = size.height;
		_size = size;
        //_top_left= Point(); Pas besoin de l'appeler car contructeur par défaut sera appelé
        }
    Square::Square(ei_size_t size , Point pt)
        {
			size.width = size.height;
			_size = size;
            _top_left = Point(pt);
            
        }
    
    Square::Square(ei_size_t size, unsigned int x , unsigned int y)
   
    {
		size.width = size.height;
		_size = size;
        _top_left.setX(x);
        _top_left.setY(y);
    }

    int Square::getTopLeft_x() const {
        return _top_left.getX();
    }


    int Square::getTopLeft_y() const {
        return _top_left.getY();
    }


    Point Square::getTopLeft() const {
        return _top_left;
    }


    ei_size_t Square::getSize()  {
		if(_size.width != _size.height)
			_size.width = _size.height;
        return _size;
    }

    int Square::getwidth() const {
        return _size.width;
    }

    int Square::getheight() const {
        return _size.height;
    }

    void Square::setheight( int height){
        _size.height = height;
    }

    void Square::setwidth( int width){
        _size.width = width;
    }

    void Square::set_pt_x( int x){
        _top_left.setX(x);
    }


    void Square::set_pt_y( int y){
        _top_left.setY(y);
    }
    Square::~Square(){}

    void Square::draw(ei_surface_t surface, ei_surface_t r){ 
		
        ei_point_t r_point;
        r_point.x = _top_left.getX();
        r_point.y = _top_left.getY();
        ei_copy_surface(surface, r, &r_point, EI_TRUE);
        hw_surface_unlock(r);
        hw_surface_free(r);
    }
    void Square::setPosition(const Point &v){
        _top_left.setX(v.getX());
        _top_left.setY(v.getY());
    }
    void Square::setPosition(float x , float y){
        _top_left.setX((int)x);
        _top_left.setY((int)y);
    }

    void Square::setSpeed(const Point &speed){
        _point_speed.setX(speed.getX());
        _point_speed.setY(speed.getY());
    }
    Point Square::getSpeed()const{
        return _point_speed;
    }
