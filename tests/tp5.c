#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "ei_types.h"
#include "ei_main.h"
#include "ei_draw.h"
#include "ei_event.h"
#include "hw_interface.h"


#define ALLEGRO_KEY_UP  84
#define ALLEGRO_KEY_DOWN  85
#define ALLEGRO_KEY_LEFT  82
#define ALLEGRO_KEY_RIGHT  83
#define ALLEGRO_KEY_ESCAPE  59


typedef struct image_data
{

    ei_surface_t main_window;
    ei_size_t image_size;
    ei_surface_t image;
    ei_surface_t filler;
    ei_surface_t image_mouse;
    ei_point_t *draw_pos2;
    ei_point_t *draw_pos_mouse;
    ei_point_t *origin_pos_mouse;
    ei_point_t * origin_pos;

} s_img;

void * update_display(s_img * vs_img)
{
    hw_surface_lock(vs_img->main_window);
    // Update ball keyboard image
    if (vs_img->draw_pos2->x != vs_img->origin_pos->x || vs_img->draw_pos2->y != vs_img->origin_pos->y)
    {
        ei_copy_surface(vs_img->main_window, vs_img->filler, vs_img->origin_pos, EI_FALSE);
        //ei_copy_surface(vs_img->main_window, vs_img->image_mouse, vs_img->draw_pos_mouse, EI_TRUE);
        ei_copy_surface(vs_img->main_window, vs_img->image, vs_img->draw_pos2, EI_TRUE);
    }
    // Update ball mouse image
    if (vs_img->draw_pos_mouse->x != vs_img->origin_pos_mouse->x || vs_img->draw_pos_mouse->y != vs_img->origin_pos_mouse->y)
    {
        ei_copy_surface(vs_img->main_window, vs_img->filler, vs_img->origin_pos_mouse, EI_FALSE);
        
        ei_copy_surface(vs_img->main_window, vs_img->image, vs_img->draw_pos2, EI_TRUE);

        ei_copy_surface(vs_img->main_window, vs_img->image_mouse, vs_img->draw_pos_mouse, EI_TRUE);
    }

    // Reassigned new positions
    vs_img->origin_pos->x = vs_img->draw_pos2->x;
    vs_img->origin_pos->y = vs_img->draw_pos2->y;

    // Reassigned new positions
    vs_img->origin_pos_mouse->x = vs_img->draw_pos_mouse->x;
    vs_img->origin_pos_mouse->y = vs_img->draw_pos_mouse->y;
    hw_surface_unlock(vs_img->main_window);
    hw_surface_update_rects(NULL);
}

int ei_main(int argc, char** argv)
{
    ei_surface_t main_window = NULL;
    ei_size_t main_window_size = {640, 480};
    ei_event_t event;
    ei_bool_t doexit = EI_FALSE;
    ei_color_t white = {0xff, 0xff, 0xff, 0xaa};
    ei_color_t red = { 0xff, 0x00, 0x00, 0xff };
    ei_surface_t image, ball;
    int key = 0;
    ei_bool_t stateUP,stateDOWN,stateLEFT,stateRIGHT; // state directional condition
    ei_size_t image_size,ball_size;
    ei_point_t draw_pos_mouse = {0, 0};
    ei_point_t draw_pos2 = {0, 0}; // keyboard ball position
    ei_point_t origin = {0, 0};    // keyboard origin position
    ei_point_t origin_mouse = {0, 0};

    // Init acces to hardware.
    hw_init();

    // Create the main window.
    main_window = hw_create_window(&main_window_size, EI_FALSE);

    // Load ball image
    image = hw_image_load(DATA_DIR"ball.png");
    image_size = hw_surface_get_size(image);
    ball = hw_image_load(DATA_DIR"ball.png");
    ball_size = hw_surface_get_size(image);
    
    //Surface used to fill the ball image by a white surface
    ei_surface_t filler = hw_surface_create(main_window,&ball_size);
    ei_fill(filler,&white,EI_FALSE);
    
    //Assigned struct variables to update display
    s_img * vs_img = (s_img *) malloc (sizeof(s_img));
    vs_img->main_window = main_window;
    vs_img->image_size = ball_size;
    vs_img->image = ball;
    vs_img->image_mouse = image;
    vs_img->filler = filler;
    vs_img->draw_pos2 = &draw_pos2;
    vs_img->draw_pos_mouse = &draw_pos_mouse;
    vs_img->origin_pos = &origin;
    vs_img->origin_pos_mouse= &origin_mouse;

    //stop limit window conditions 
    int stop_width_size  = main_window_size.width - image_size.width;
    int stop_height_size = main_window_size.height - image_size.height;
    
    //Init copy image on the screen
    hw_surface_lock(main_window);
    ei_fill(main_window, &white, EI_FALSE);
    ei_copy_surface(main_window, image, &draw_pos_mouse, EI_TRUE);
    ei_copy_surface(main_window, ball, &draw_pos2, EI_TRUE);
    hw_surface_unlock(main_window);
    hw_surface_update_rects(NULL);
    
    // Wait for a key press.
    event.type = ei_ev_none;
    double frequency=1 / 60;
    double current_time = hw_now();
    while (1)
    {
        // Close condition : close button and escape button
        if( event.type == ei_ev_display && event.param.display.closed == EI_TRUE
                || event.type == ei_ev_keydown && event.param.key.key_sym == ALLEGRO_KEY_ESCAPE)  // 59 == escape
        {
            doexit = EI_TRUE;
            hw_quit();
            free(vs_img);
            return 0;
            
        }
        // if directional key have been pressed , update stzte variables
        if(event.type== ei_ev_keydown)
        {
            
            key = event.param.key.key_sym;
            
            if (key == ALLEGRO_KEY_UP)
                stateUP = EI_TRUE;
            if (key == ALLEGRO_KEY_DOWN)
                stateDOWN = EI_TRUE;
            if (key == ALLEGRO_KEY_LEFT)
                stateLEFT = EI_TRUE;
            if (key == ALLEGRO_KEY_RIGHT)
                stateRIGHT = EI_TRUE;     
        }
        // if directional key has been released update state variables
        if(event.type == ei_ev_keyup )
        {
			
            stateUP = EI_FALSE;
            stateDOWN = EI_FALSE;
            stateLEFT = EI_FALSE;
            stateRIGHT = EI_FALSE;
        }

        // Left up Diagonal 
        if (stateUP == EI_TRUE && stateLEFT==EI_TRUE)
        {
            if(draw_pos2.y>=1 && draw_pos2.x>=1 )
            {
                draw_pos2.y -= 1;
                draw_pos2.x -= 1;
            }
        }
        //Right up Diagonal
        else if (stateUP == EI_TRUE && stateRIGHT==EI_TRUE)
        {
            if(draw_pos2.y>=1 && draw_pos2.x<stop_width_size)
            {
                draw_pos2.y -= 1;
                draw_pos2.x += 1;
            }
        }
        else if (stateUP == EI_TRUE)
        {
            if(key == ALLEGRO_KEY_UP && draw_pos2.y>=1)
                draw_pos2.y -=1;
        }

        //Down Left diagonal
        if (stateDOWN == EI_TRUE && stateLEFT==EI_TRUE)
        {
            if(draw_pos2.y<stop_height_size && draw_pos2.x >=1)
            {
                draw_pos2.y += 1;
                draw_pos2.x -= 1;
            }
        }
        //Down right diagonal
        else if (stateDOWN == EI_TRUE && stateRIGHT==EI_TRUE)
        {
            if (draw_pos2.y< stop_height_size && draw_pos2.x < stop_width_size)
            {
                draw_pos2.y += 1;
                draw_pos2.x += 1;
            }
        }
        else if (stateDOWN == EI_TRUE)
        {
            if(key == ALLEGRO_KEY_DOWN && draw_pos2.y<stop_height_size)
                draw_pos2.y +=1;
        }

        if (stateLEFT)
        {
            if(key == ALLEGRO_KEY_LEFT && draw_pos2.x>=1)
                draw_pos2.x -=1;
        }

        if (stateRIGHT)
        {
            if(key == ALLEGRO_KEY_RIGHT && draw_pos2.x<stop_width_size)
                draw_pos2.x +=1;
        }

        if (event.type == ei_ev_mouse_move)
        {
            draw_pos_mouse.x = event.param.mouse.where.x - (image_size.width / 2);
            draw_pos_mouse.y = event.param.mouse.where.y - (image_size.height / 2);

            if (draw_pos_mouse.y + image_size.height >main_window_size.height)
                draw_pos_mouse.y = stop_height_size;
            if (draw_pos_mouse.x + image_size.width > main_window_size.width)
                draw_pos_mouse.x = stop_width_size;
            if (draw_pos_mouse.y < 0)
                draw_pos_mouse.y = 0;
            if (draw_pos_mouse.x < 0)
                draw_pos_mouse.x = 0;
        }
        // update 60 fps
        if(hw_now()-current_time>frequency)
        {
            // update display
            update_display(vs_img);
            current_time = hw_now();
        }
        hw_event_wait_next(&event);
    }





    // Free hardware resources.
    hw_quit();
    free(vs_img);

    // Terminate program with no error code.
    return 0;
}
