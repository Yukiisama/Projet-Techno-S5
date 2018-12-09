#include <stdlib.h>
#include <stdio.h>
#include "ei_types.h"
#include "ei_main.h"
#include "ei_draw.h"
#include "ei_event.h"
#include "hw_interface.h"
#include "Point.h"
#include <allegro5/allegro.h>
#include <iostream>
#include "viewer.h"

int ei_main(int argc, char** argv)
{
    ei_surface_t main_window = NULL;
    ei_size_t main_window_size = {640, 480};
    ei_event_t event;
    ei_bool_t doexit = EI_FALSE;
    ei_color_t white = {0xff, 0xff, 0xff, 0xaa};    
    Point p = Point();
    std::cout << p << std::endl;
    Viewer viewer(main_window_size);

    // Init acces to hardware.
    hw_init();

    // Create the main window.
    main_window = hw_create_window(&main_window_size, EI_FALSE);

    hw_surface_lock(main_window);
    ei_fill(main_window, &white, EI_FALSE);
    hw_surface_unlock(main_window);
    hw_surface_update_rects(NULL);

    double time = hw_now();

    ei_bool_t redraw = EI_FALSE;

    // Wait for an event.
    event.type = ei_ev_none;
    while (doexit != EI_TRUE) {

        hw_event_wait_next(&event);
        if (event.type == ei_ev_keyup || event.type == ei_ev_keydown) {
            if (event.param.key.key_sym == ALLEGRO_KEY_ESCAPE)
                doexit = EI_TRUE;
            else
                viewer.keyPressed(event.param.key.key_sym);
        } else if (event.type == ei_ev_display) {
            if (event.param.display.closed)
                doexit = EI_TRUE;
        } else if(event.type == ei_ev_mouse_move) {
            viewer.mouseMoved(event.param.mouse.where.x, event.param.mouse.where.y);
        } else if(event.type == ei_ev_mouse_buttonup) {
            viewer.mousePressed(event.param.mouse.button_number,0);
        } else if(event.type == ei_ev_mouse_buttondown) {
            viewer.mousePressed(event.param.mouse.button_number,1);
        } else if(event.type == ei_ev_timer) {
            redraw = EI_TRUE;
        }

        if(hw_now() - time > 1.0/60.0 || redraw == EI_TRUE) {
            // Refresh main_window
            hw_surface_lock(main_window);
            ei_fill(main_window, &white, EI_FALSE);

            viewer.updateScene();
            viewer.display(main_window);

            hw_surface_unlock(main_window);
            hw_surface_update_rects(NULL);

            time = hw_now();
            redraw = EI_FALSE;
        }
    }

    // Free hardware resources.
    hw_quit();

    // Terminate program with no error code.
    return 0;
}
