#include <stdlib.h>
#include <stdio.h>
#include "ei_types.h"
#include "ei_main.h"
#include "ei_draw.h"
#include "ei_event.h"
#include "hw_interface.h"

int ei_main(int argc, char* argv[])
{
    ei_surface_t main_window = NULL;
    ei_size_t		 main_window_size;
    ei_event_t event;
    ei_color_t black		= { 0x00, 0x00, 0x00, 0xff };
    ei_color_t white		= { 0xff, 0xff, 0xff, 0xff };

    // Init acces to hardware.
    hw_init();

    // Create the main window.
    main_window_size.width	= 640;
    main_window_size.height	= 480;
    main_window = hw_create_window(&main_window_size, EI_FALSE);

    
    hw_surface_lock(main_window);
    
    ei_fill(main_window, &white, EI_FALSE);
    
    ei_point_t start, end, pos_text;
    start.x = 320;
    start.y = 240;
    int step1 = 50, step2=100;
    
    for (int k=-step2; k<=step2; k+=step1) {
        end.x = start.x+k;
        for (int l=-step2; l<=step2; l+=2*step2) {
            end.y = start.y+l;
            ei_draw_line_correction(main_window, start,end, black);
        }
    }
    for (int l=-step2; l<=step2; l+=step1) {
        end.y = start.y+l;

        for (int k=-step2; k<=step2; k+=2*step2) {
            end.x = start.x+k;
            ei_draw_line_correction(main_window, start,end, black);
        }
    }
    
    ei_font_t font = hw_text_font_create(ei_default_font_filename, 12);
    char text[50];
    pos_text.x = start.x-step2-50;
    pos_text.y = start.y-step2-10;
    sprintf(text, "(%d, %d)", start.x-step2,start.y-step2);
    ei_draw_text(main_window, &pos_text, text, font, &ei_font_default_color);
    pos_text.x = start.x+step2+5;
    pos_text.y = start.y-step2-10;
    sprintf(text, "(%d, %d)", start.x-step2,start.y-step2);
    ei_draw_text(main_window, &pos_text, text, font, &ei_font_default_color);
    pos_text.x = start.x-step2-50;
    pos_text.y = start.y+step2+5;
    sprintf(text, "(%d, %d)", start.x-step2,start.y-step2);
    ei_draw_text(main_window, &pos_text, text, font, &ei_font_default_color);
    pos_text.x = start.x+step2+5;
    pos_text.y = start.y+step2+5;
    sprintf(text, "(%d, %d)", start.x-step2,start.y-step2);
    ei_draw_text(main_window, &pos_text, text, font, &ei_font_default_color);
    
    //polyline
    ei_size_t text_size;
    hw_text_compute_size(text, font, &text_size.width, &text_size.height);
    ei_linked_point_t polyline;
    ei_point_t start_pos;
    
    start_pos.x = pos_text.x-5;
    start_pos.y = pos_text.y-5;
    polyline.point = start_pos;
    polyline.next = (ei_linked_point_t*) malloc(sizeof(struct ei_linked_point_t));
    polyline.next->point = (ei_point_t) {start_pos.x + text_size.width+10, start_pos.y};
    polyline.next->next = (ei_linked_point_t*) malloc(sizeof(struct ei_linked_point_t));
    polyline.next->next->point = (ei_point_t) {start_pos.x + text_size.width+10, start_pos.y + text_size.height+10};
    polyline.next->next->next  = (ei_linked_point_t*) malloc(sizeof(struct ei_linked_point_t));
    polyline.next->next->next->point = (ei_point_t) {start_pos.x, start_pos.y + text_size.height+10};
    polyline.next->next->next->next = (ei_linked_point_t*) malloc(sizeof(struct ei_linked_point_t));
    polyline.next->next->next->next->point = start_pos;
    polyline.next->next->next->next->next = NULL;
    
    ei_draw_polyline_correction(main_window, &polyline, black);
    
    hw_surface_unlock(main_window);

    
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
