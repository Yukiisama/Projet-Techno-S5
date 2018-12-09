#ifndef VIEWER_H
#define VIEWER_H
#include "Rectangle.h"
#include "Square.h"
#include "ei_types.h"
#include "hw_interface.h"
#include <vector>
using namespace std;


class Viewer
{
public:
    //! Constructor
    Viewer(ei_size_t size);
    virtual ~Viewer();

    void display(ei_surface_t surface);
    void updateScene();
    void reshape(int w, int h);

    // events
    void mousePressed(int button, int action);
    void mouseMoved(int x, int y);
    void keyPressed(int key);

private:
    ei_size_t _size;
    float _scalingFactor;
    bool _growing;
    ei_color_t _red;
    Square _square; // to add in vector 
    Rectangle _rectangle;   //Can be replace by Square _rectangle if you want a square (Square herited of Shape)
    int width;
    int height;
    vector<Shape> generic_shape;
};

#endif
