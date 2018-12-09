#include <stdlib.h>

#include "ei_types.h"
#include "ei_main.h"
#include "ei_draw.h"
#include "ei_event.h"
#include "hw_interface.h"

#include <math.h>

/**
 * \brief   Allocate and set the list of points defining an arc
 *
 * @param   center     Center of the arc
 * @param   radius    Radius of the arc
 * @param   start_angle   Beginning angle
 * @param   end_angle   Ending angle
 * @return  Returns the list of points defining the arc.
 */
ei_linked_point_t* arc(ei_point_t center, float radius, int start_angle, int end_angle)
{
    ei_linked_point_t* list = (ei_linked_point_t*) malloc(sizeof(ei_linked_point_t));
    ei_linked_point_t* start = list;
    
    float angle = (end_angle - start_angle) * M_PI/180.f;
    int nbpts = radius * fabs(angle);
    for(int i=0; i<=nbpts; i++){
        list->next = (ei_linked_point_t*) malloc(sizeof(ei_linked_point_t));
        list = list->next;
        list->point.x = radius * cosf(start_angle * M_PI/180.f + (float)i * angle / (float)nbpts) + center.x;
        list->point.y = radius * sinf(start_angle * M_PI/180.f + (float)i * angle / (float)nbpts) + center.y;
        //printf("%d,%d\n", list->point.x, list->point.y);
    }
    list->next = NULL;
    return start->next;
}

typedef enum {BT_TOP, BT_BOTTOM, BT_FULL} bt_part;
/**
 * \brief   Defines the list of points to draw a rounded frame
 *
 * @param   rect    rectangle
 * @param   radius    Radius of the arcs
 * @param   part   Only set the pints for the TOP, BOTTOM or ALL part of the rounded frame
 * @return  Returns the list of points defining the rounded frame
 */
ei_linked_point_t* rounded_frame(ei_rect_t *rect, float radius, bt_part part)
{
    ei_point_t pt = rect->top_left;
    ei_linked_point_t* list, *start;
    if(part != BT_BOTTOM){
        pt.x += radius;
        pt.y += (rect->size.height - radius);
        list = arc(pt, radius, 135, 180);
        start = list;
        while(list->next)
            list = list->next;
        pt.y -= (rect->size.height - 2.f * radius);
        list->next = arc(pt, radius, 180, 270);
        while(list->next)
            list = list->next;
        pt.x += (rect->size.width - 2.f * radius);
        list->next = arc(pt, radius, 270, 315);
        while(list->next)
            list = list->next;
    }
    
    if(part == BT_TOP) {
        list->next = (ei_linked_point_t*) malloc(sizeof(ei_linked_point_t));
        list = list->next;
        list->point.x = rect->top_left.x + 2*rect->size.width / 3;
        list->point.y = rect->top_left.y + rect->size.height / 2;
        list->next = (ei_linked_point_t*) malloc(sizeof(ei_linked_point_t));
        list = list->next;
        list->point.x = rect->top_left.x + rect->size.width / 3;
        list->point.y = rect->top_left.y + rect->size.height / 2;
        list->next = NULL;
        return start;
    }
    if(part == BT_BOTTOM){
        pt.x += rect->size.width - radius;
        pt.y += radius;
        list = arc(pt, radius, 315, 360);
        start = list;
    }else{
        list->next = arc(pt, radius, 315, 360);
    }
    
    list->next = arc(pt, radius, 315, 360);
    while(list->next)
        list = list->next;
    pt.y += (rect->size.height - 2.f * radius);
    list->next = arc(pt, radius, 0, 90);
    while(list->next)
        list = list->next;
    pt.x -= (rect->size.width - 2.f * radius);
    list->next = arc(pt, radius, 90, 135);
    while(list->next)
        list = list->next;
    if(part == BT_BOTTOM){
        list->next = (ei_linked_point_t*) malloc(sizeof(ei_linked_point_t));
        list = list->next;
        list->point.x = rect->top_left.x + rect->size.width / 3;
        list->point.y = rect->top_left.y + rect->size.height / 2;
        list->next = (ei_linked_point_t*) malloc(sizeof(ei_linked_point_t));
        list = list->next;
        list->point.x = rect->top_left.x + 2*rect->size.width / 3;
        list->point.y = rect->top_left.y + rect->size.height / 2;
        list->next = NULL;
    }
    return start;
}
/**
 * \brief   Draw a rounded  button
 */
void draw_button(ei_surface_t surface, ei_rect_t rect, float radius, const char* text)
{
    ei_color_t lgrey = { 0xcf, 0xcf, 0xcf, 0xff };
    ei_color_t dgrey = { 0x6f, 0x6f, 0x6f, 0xff };
    ei_color_t white = { 0xff, 0xff, 0xff, 0xff };
    
    ei_linked_point_t* rect_top = rounded_frame(&rect, radius, BT_TOP);
    ei_linked_point_t* rect_bottom = rounded_frame(&rect, radius, BT_BOTTOM);
    rect.top_left.x += 5;
    rect.top_left.y += 5;
    rect.size.width  -= 10;
    rect.size.height -= 10;
    ei_linked_point_t* rect_full = rounded_frame(&rect, radius-5, BT_FULL);
    
    ei_draw_polygon_correction(surface, rect_top, lgrey);
    ei_draw_polygon_correction(surface, rect_bottom, dgrey);
    ei_draw_polygon_correction(surface, rect_full, ei_default_background_color);
    
    // text
    ei_font_t font = hw_text_font_create(ei_default_font_filename, ei_font_default_size);
    int width, height;
    hw_text_compute_size(text,font,&width,&height);
    ei_point_t pos = rect.top_left;
    pos.x += (rect.size.width - width) / 2.f;
    pos.y += (rect.size.height - height) / 2.f;
    ei_draw_text(surface, &pos, text, font, &white);
}


int ei_main(int argc, char* argv[])
{
    ei_surface_t main_window = NULL;
    ei_size_t    main_window_size;
    ei_event_t   event;
    ei_color_t red   = { 0xff, 0x00, 0x00, 0xff };
    
    ei_linked_point_t* arc_list = arc( (ei_point_t){50,50}, 40, 75, -75);
    
    ei_rect_t rect;
    rect.top_left = (ei_point_t){100,100};
    rect.size = (ei_size_t){200, 100};
    
    // Init acces to hardware.
    hw_init();
    
    // Create the main window.
    main_window_size.width	= 640;
    main_window_size.height	= 480;
    main_window = hw_create_window(&main_window_size, EI_FALSE);
    
    hw_surface_lock(main_window);
    
    ei_fill(main_window, &ei_default_background_color, EI_TRUE);
    
    ei_draw_polyline_correction(main_window, arc_list, red);
    
    draw_button(main_window, rect, 20, "Button");
    
    hw_surface_unlock(main_window);
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
