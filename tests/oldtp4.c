#include <stdlib.h>
#include "ei_types.h"
#include "ei_main.h"
#include "ei_draw.h"
#include "ei_event.h"
#include "hw_interface.h"
int ei_main(int argc, char** argv)
{
    ei_surface_t main_window = NULL;
    ei_size_t		 main_window_size;
    ei_event_t event;
    ei_color_t black		= { 0x00, 0x00, 0x00, 0xff };
    ei_color_t white		= { 0xff, 0xff, 0xff, 0xff };
    ei_color_t transp_cyan	= { 0x00, 0xff, 0xff, 0x88 };
    int	i;
    ei_linked_point_t	points[6];
    ei_linked_point_t	triangle[3];
    int	coords[] = { 40, 80, 350, 20, 580, 150, 520, 430, 250, 300, 20, 400 };   
    
    // Init acces to hardware.
    hw_init();
    
    // Create the main window.
    main_window_size.width	= 640;
    main_window_size.height	= 480;
    main_window = hw_create_window(&main_window_size, EI_FALSE);
    
    
    // Define the polygon vertices.
    for (int i = 0; i < 6; i++) {
        points[i].point.x = coords[i * 2];
        points[i].point.y = coords[i * 2 + 1];
        if (i < 5)
            points[i].next = &(points[i + 1]);
        else
            points[i].next = NULL;
    }
    
    // Define the triangle vertices.
    for (i = 3; i < 6; i++) {
        triangle[i - 3].point.x	= coords[i * 2];
        triangle[i - 3].point.y	= coords[i * 2 + 1];
        if (i < 5)
            triangle[i - 3].next = &(triangle[i - 2]);
        else
            triangle[i - 3].next = NULL;
    }
    
    // Lock the surface for drawing, fill, draw polygon, unlock, update screen.
      ei_point_t  centre;
    
    centre.x=200; centre.y=200;

    ei_rect_t rect;
    rect.top_left=centre;
    rect.size.width=300;
    rect.size.height=150;
    hw_surface_lock(main_window);

    ei_fill(main_window, &white, EI_FALSE);

    //ei_draw_polygon(main_window, points, black);
    ei_draw_polyline(main_window, rounded_frame(&rect,50,0), black);
    //ei_draw_polygon(main_window, triangle, transp_cyan);

    hw_surface_unlock(main_window);

    hw_surface_update_rects(NULL);

    //display
    hw_surface_update_rects(NULL);
    
    // Wait for a key press.
    event.type = ei_ev_none;
    while (event.type != ei_ev_keydown) {
        hw_event_wait_next(&event);
    }
    
    // Free hardware resources.
    hw_quit();
    
    // Terminate program with no error code.
    return 0;
}
