#include <stdlib.h>

#include "ei_event.h"
#include "hw_interface.h"
#include <stdio.h>

//Colors for terminal
#define BLUE   "\x1B[34m"
#define GREEN   "\x1B[32m"
#define YELLOW   "\x1B[33m"
#define RESET "\x1B[0m"
//END colors for terminal

int ei_main(int argc, char** argv)
{
	// Init of environnement variables
	ei_surface_t  main_window = NULL;
	ei_size_t     main_window_size;
	ei_event_t    event;


	// Init acces to hardware.
	hw_init();

	// Create the main window.
	main_window_size.width	= 640;
	main_window_size.height	= 480;
	main_window = hw_create_window(&main_window_size, EI_FALSE);
    main_window_size = hw_surface_get_size(main_window);
    //Verify parameters

    printf(GREEN "Width of the window is %d  ; Height of the window is %d\n" RESET, main_window_size.width , main_window_size.height);

    //Get pixel to change afterwards

    ei_point_t pos = { 10 , 20 } ;
    ei_color_t color =hw_get_pixel(main_window,pos);
    ei_color_t new_color = {0,0,255,255}; // BLUE COLOR 
    //Verify pixel & change color
    printf ( "Check color pixel at position (10 ,20 ) before turning blue \n");
    printf( YELLOW "Blue %d | alpha %d | green %d | red %d\n" RESET ,(int) color.blue , (int) color.alpha , (int) color.green , (int) color.red);
    
    //Gains exclusive access to a surface. Every call to hw_surface_lock must be matched by a call to hw_surface_unlock. 
    hw_surface_lock(main_window);

    //Put new pixel color 
    hw_put_pixel(main_window,pos,new_color);
    color = hw_get_pixel(main_window,pos);
    
    //Last check up new color pixel /!\ blue
	printf ( "Check color pixel at position (10 ,20 ) after turning blue \n");
    printf( BLUE "Blue %d  |  alpha %d | green %d | red %d\n" RESET ,(int) color.blue , (int) color.alpha , (int) color.green , (int) color.red);
    
	// Release the surface which was lock by hw_surface_lock
    hw_surface_unlock(main_window);
    // clear out the buffer
    fflush(stdout);



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
