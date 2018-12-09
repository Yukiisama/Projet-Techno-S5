#include "ei_draw.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

//Colors for terminal
#define BLUE   "\x1B[34m"
#define BOLDRED     "\033[1m\033[31m"
#define GREEN   "\x1B[32m"
#define YELLOW   "\x1B[33m"
#define RESET "\x1B[0m"
//END colors for terminal

static inline ei_color_t alpha_blend(const ei_color_t in_pixel, const ei_color_t dst_pixel)
{
    // Will result to the alpha blend of two pixels
    ei_color_t to_return;

    const double RATIO = 255;

    to_return.red =   in_pixel.alpha / RATIO  * in_pixel.red + (  1 - in_pixel.alpha/RATIO) * dst_pixel.red;
    to_return.blue =  in_pixel.alpha / RATIO * in_pixel.blue + ( 1- in_pixel.alpha/RATIO) * dst_pixel.blue;
    to_return.green = in_pixel.alpha / RATIO * in_pixel.green + ( 1 - in_pixel.alpha/RATIO) * dst_pixel.green;
    to_return.alpha =  RATIO;

    return to_return;
}




void ei_draw_text(ei_surface_t surface, const ei_point_t* where,
                  const char* text, const ei_font_t font,
                  const ei_color_t* color)
{



    ei_font_t Font = font;
    ei_size_t size_surface;

    // ERROR CASES

    if (surface == NULL){
        fprintf(stderr,"Something wrong with surface , NULL POINTER");
        exit(EXIT_FAILURE);
    }


    if(color == NULL){
        fprintf(stderr, " The text color can't be NULL  ");
        exit(EXIT_FAILURE);
    }

    if(text == NULL){
        fprintf(stderr, " The text color can't be NULL  ");
        exit(EXIT_FAILURE);
    }
    if (font == NULL){

        //If NULL, the ei_default_font is used.
        Font = hw_text_font_create(ei_default_font_filename,ei_font_default_size);
    }

    size_surface = hw_surface_get_size(surface);


    if (where->x >= size_surface.width || where->y >= size_surface.height){
        fprintf(stderr,BOLDRED " The text hasn't been drawn , the position you wanted exceed the limits of the surface" RESET);
    }

    else{
        hw_surface_lock(surface);
        ei_surface_t surface_text = hw_text_create_surface(text,Font,color);

        // After the text_surface has been created copied it on the surface given.
        ei_copy_surface(surface,surface_text,where,EI_TRUE);

        // Copy surface unlock already the surface!
    }


}


void ei_fill(ei_surface_t surface, const ei_color_t* color, const ei_bool_t use_alpha)
{
    if (surface == NULL){
        fprintf(stderr,"Something wrong with surface , NULL POINTER");
        exit(EXIT_FAILURE);
    }

    ei_color_t pixel;

    //If NULL, it means that the caller want it painted black (opaque, \ref ei_font_default_color).
    if (color == NULL){
        pixel = ei_default_background_color;
    }
    else
        pixel =*(color);

    ei_surface_t main_window = surface;

    // get main window size
    ei_size_t main_window_size = hw_surface_get_size(main_window);

    // LOCK SURFACE BEFORE EDITING
    hw_surface_lock(main_window);
    ei_point_t pos ={0,0};

    // pixel_alpha & pixel_result are only used if use_alpha true ( i.e if transparency needed).
    ei_color_t pixel_alpha;
    ei_color_t pixel_result;

    // Fill the whole surface in the color user given
    for ( pos.x=0 ; pos.x < main_window_size.width ; pos.x++) {
        for (pos.y =0 ; pos.y < main_window_size.height  ; pos.y++){

            //If  use alpha true, the final pixels are a combination of source and destination pixels
            // weighted by the source alpha channel. The transparency of the final pixels is set to opaque.
            if(use_alpha){
                pixel_alpha = hw_get_pixel(main_window,pos);
                pixel_result = alpha_blend(pixel,pixel_alpha);
                hw_put_pixel(main_window,pos,pixel_result);

            }

            //If false, the final pixels are an exact copy of the source pixels, including the alpha channel.
            else{
                hw_put_pixel(main_window,pos,pixel);
            }

        }
    }

    //Unlock surface when all processing are over
    hw_surface_unlock(main_window);

}


void ei_copy_surface(ei_surface_t destination, const ei_surface_t source,
                     const ei_point_t* where, const ei_bool_t use_alpha)
{
    if (destination == NULL || source == NULL){
        fprintf(stderr,"Something wrong with surface , NULL POINTER");
        exit(EXIT_FAILURE);
    }

    ei_surface_t source_window = source;
    ei_surface_t dest_window = destination;

    // get windows size
    ei_size_t source_window_size = hw_surface_get_size(source_window);
    ei_size_t dest_window_size = hw_surface_get_size(dest_window);

    // LOCK SURFACE BEFORE EDITING
    hw_surface_lock(dest_window);


    //Init pixel : color default , pos (0,0) if where is NULL
    ei_point_t pos ={0,0};
    ei_color_t pixel ={0,0,0,0};

    //Pixel_dest & Pixel_result will be only used if use_alpha is true;
    ei_color_t pixel_dest;
    ei_color_t pixel_result;

    ei_point_t new = {0,0};

    if (where !=NULL) new =*(where);


    //Only processing if position given don't exceed the size of the window
    if (!(new.x >= dest_window_size.width || new.y >=dest_window_size.height)){

        // Fill the surface beginning at pos.

        for ( pos.x=0 , new.x=(*where).x; pos.x < source_window_size.width ; pos.x++, new.x++) {
            for (pos.y =0 , new.y=(*where).y; pos.y < source_window_size.height  ; pos.y++,new.y++){

                pixel= hw_get_pixel(source_window,pos);

                //If true, the final pixels are a combination of source and destination pixels weighted by the source alpha channel.

                if(use_alpha){
                    pixel_dest = hw_get_pixel(dest_window,new);
                    pixel_result = alpha_blend(pixel,pixel_dest);
                    hw_put_pixel(dest_window,new,pixel_result);

                }
                else{
                    hw_put_pixel(dest_window,new,pixel);
                }

            }
        }
    }
    else printf(BOLDRED "Your surface hasn't been copied because the position you gave exceed the extremity of the surface \n " RESET);

    //Release surface when all processing are over
    hw_surface_unlock(dest_window);
}
