#include "viewer.h"
#include "Rectangle.h"
#include "ei_draw.h"
#include "Square.h"
#include <string>
#include <iostream>

using namespace std;

Viewer::Viewer(ei_size_t size):
    _size(size),
    _scalingFactor(0.5),
    _growing(true),
    _rectangle(size)
    {
    
    _red.red = 255;
    _red.green = 0;
    _red.blue = 0;
    _red.alpha = 255;
}

Viewer::~Viewer(){
}

void Viewer::display(ei_surface_t surface){
    const ei_size_t r_size = _rectangle.getSize();
    ei_surface_t r = hw_surface_create(surface, &r_size);
    hw_surface_lock(r);
    ei_fill(r, &_red, EI_TRUE);
    _rectangle.draw(surface,r);
}

void Viewer::updateScene() 
{

    if(_growing){
        _scalingFactor += 0.005;
        _growing = _scalingFactor < 0.7; // grow square until _halfSize >= 0.8
    } else {
        _scalingFactor -= 0.005;
        _growing = _scalingFactor < 0.4; // grow square until _halfSize <= 0.3
    }
    // update rectangle size and position
    _rectangle.setwidth (_scalingFactor * _size.width);
    _rectangle.setheight( _scalingFactor * _size.height);
    float x =(_size.width - _rectangle.getwidth()) / 2.f;
    float y =(_size.height - _rectangle.getheight()) / 2.f;
    _rectangle.setPosition(x,y);
    

}


////////////////////////////////////////////////////////////////////////////////
// Events

/*!
   callback to manage mouse : called when the user presses (action==0) or releases (action==0) a mouse button
 */
void Viewer::mousePressed(int button, int action){
    //CODE SPEED HERE
}


/*!
   callback to manage mouse : called when the user moves the mouse
 */
void Viewer::mouseMoved(int x, int y){
    //CODE SPEED HERE
}


/*!
   callback to manage keyboard interactions
 */
void Viewer::keyPressed(int key){

}
