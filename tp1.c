#include <stdlib.h>

#include "ei_event.h"
#include "hw_interface.h"

int ei_main(int argc, char** argv)
{
	ei_surface_t main_window = NULL;
	ei_size_t		 main_window_size;
	ei_event_t event;


	// Init acces to hardware.
	hw_init();

	// Create the main window.
	main_window_size.width	= 640;
	main_window_size.height	= 480;
	main_window = hw_create_window(&main_window_size, EI_FALSE);


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
