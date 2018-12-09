#ifndef SHAPE_H
#define SHAPE_H

#include "ei_types.h"
#include "hw_interface.h"
#include "Point.h"

class Shape
{
public:
virtual void getName();
virtual void  draw(ei_surface_t surface, ei_surface_t r)= 0; // =0 means "pure virtual"
private:
Point p;
char * name;
};
#endif
