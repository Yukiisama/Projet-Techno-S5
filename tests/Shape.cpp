#include "Shape.h"
#include "ei_draw.h"
#include <string>
#include <iostream>

void Shape::getName(){
    std::cout << "J'hérite de Shape et je suis  "<< name << std::endl;
}
void Shape::draw(ei_surface_t surface, ei_surface_t r){
	// Default Implémentation
}
