#include <stdlib.h>
#include <stdio.h>
#include "ei_types.h"
#include "ei_main.h"
#include "ei_draw.h"
#include "ei_event.h"
#include "hw_interface.h"

#include <allegro5/allegro.h>

int ei_main(int argc, char** argv)
{
    ei_surface_t main_window = NULL;
    ei_size_t main_window_size = {640, 480};
    ei_event_t event;
    ei_bool_t doexit = EI_FALSE;
    ei_color_t white = {0xff, 0xff, 0xff, 0xaa};
    ei_color_t red = { 0xff, 0x00, 0x00, 0xff };
    ei_surface_t image;
    ei_size_t image_size;
    ei_point_t draw_pos1 = {0, 0}, draw_pos2;
    enum KEYS {UP, DOWN, LEFT, RIGHT};
    ei_bool_t active_keys[4] = {EI_FALSE, EI_FALSE, EI_FALSE, EI_FALSE};
    int step = 3;

    // Init acces to hardware.
    hw_init();

    // Create the main window.
    main_window = hw_create_window(&main_window_size, EI_FALSE);

    // Load ball image
    image = hw_image_load(DATA_DIR"ball.png");
    image_size = hw_surface_get_size(image);

    draw_pos2 = (ei_point_t){main_window_size.width-image_size.width, main_window_size.height-image_size.height};

    hw_surface_lock(main_window);
    ei_fill(main_window, &white, EI_FALSE);
    ei_copy_surface(main_window, image, &draw_pos1, EI_TRUE);
    hw_surface_unlock(main_window);
    hw_surface_update_rects(NULL);

    double time = hw_now();

    // Wait for an event.
    event.type = ei_ev_none;
    while (doexit != EI_TRUE) {

        hw_event_wait_next(&event);
        if (event.type == ei_ev_keyup || event.type == ei_ev_keydown) {
            if (event.param.key.key_sym == ALLEGRO_KEY_ESCAPE)
                doexit = EI_TRUE;
            else if (event.param.key.key_sym == ALLEGRO_KEY_UP)
                active_keys[UP] = (ei_bool_t)(event.type == ei_ev_keydown);
            else if (event.param.key.key_sym == ALLEGRO_KEY_DOWN)
                active_keys[DOWN] = (ei_bool_t)(event.type == ei_ev_keydown);
            else if (event.param.key.key_sym == ALLEGRO_KEY_LEFT)
                active_keys[LEFT] = (ei_bool_t)(event.type == ei_ev_keydown);
            else if (event.param.key.key_sym == ALLEGRO_KEY_RIGHT)
                active_keys[RIGHT] = (ei_bool_t)(event.type == ei_ev_keydown);
        } else if (event.type == ei_ev_display) {
            if (event.param.display.closed)
                doexit = EI_TRUE;
        } else if(event.type == ei_ev_mouse_move) {
            draw_pos2.x = event.param.mouse.where.x - image_size.width / 2;
            draw_pos2.y = event.param.mouse.where.y - image_size.height / 2;
        }

        if(draw_pos1.y > step)
            draw_pos1.y -= step * active_keys[UP];
        if(draw_pos1.y + image_size.height + step < main_window_size.height)
            draw_pos1.y += step * active_keys[DOWN];
        if(draw_pos1.x > step)
            draw_pos1.x -= step * active_keys[LEFT];
        if(draw_pos1.x + image_size.width + step < main_window_size.width)
            draw_pos1.x += step * active_keys[RIGHT];

        if(hw_now() - time > 1.0/60.0 ) {
            // Refresh main_window
            hw_surface_lock(main_window);
            ei_fill(main_window, &white, EI_FALSE);
            hw_surface_lock(image);
            ei_copy_surface(main_window, image, &draw_pos1, EI_TRUE);
            ei_copy_surface(main_window, image, &draw_pos2, EI_TRUE);

            hw_surface_unlock(image);
            hw_surface_unlock(main_window);
            hw_surface_update_rects(NULL);

            time = hw_now();
        }
    }

    // Free hardware resources.
    hw_quit();

    // Terminate program with no error code.
    return 0;
}
