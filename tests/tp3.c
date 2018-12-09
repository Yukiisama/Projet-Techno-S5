#include <stdlib.h>
#include "ei_draw.h"
#include "ei_event.h"
#include "hw_interface.h"
#include <stdio.h>


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

	// Differents point we need & colors
    ei_point_t start = {320,220};
    ei_point_t end = {440,220};
    ei_color_t color = {255,255,255,255};
    ei_color_t color2 = {0,0,0,255};
    hw_surface_lock(main_window);
    
     
    //DRAWINGS 8 octants
    
    ei_draw_line(main_window,start,end,color);
    end.y -=60 ;
    ei_draw_line(main_window,start,end,color);
    end.y -=60 ;
    ei_draw_line(main_window,start,end,color);
	
	
	
    for (int i = 0 ; i<4; i++){
	
		end.x -=60 ;
		ei_draw_line(main_window,start,end,color);
	}
    
    for (int i = 0 ; i<4; i++){
	
		end.y +=60 ;
    ei_draw_line(main_window,start,end,color);
	}
    
     for (int i = 0 ; i<4; i++){
	
		end.x +=60 ;
		ei_draw_line(main_window,start,end,color);
	}
   
	
    end.y -=60 ;
    ei_draw_line(main_window,start,end,color);
    end.y -=60 ;
    ei_draw_line(main_window,start,end,color);
    
    //END drawing 8 octants
    
		ei_point_t text_pos = { 50 , 50 };
		
		ei_draw_text(main_window,&text_pos,"   Some  text =) " , NULL , &color2);
		
		
		// Chained list of points before drawing with polyline
		ei_linked_point_t * first = malloc(sizeof(ei_linked_point_t));
		const ei_linked_point_t * copie = first;
		first -> next = malloc(sizeof(ei_linked_point_t));
		first -> point.x = 50; first->point.y = 52;
		first = first-> next; first -> point.x = 53; first->point.y = 51;
		first -> next = malloc(sizeof(ei_linked_point_t));
		first = first-> next; first -> point.x = 49; first->point.y = 53;
		first -> next = malloc(sizeof(ei_linked_point_t));
		first = first-> next; first -> point.x = 62; first->point.y = 52;
		first -> next = malloc(sizeof(ei_linked_point_t));
		first = first-> next; first -> point.x = 48; first->point.y = 55;
		first->next = NULL; 
		
	
		int  min = 0;
		int  max = 0;
		//printf( " coucou : %d \n" ,size(copie));
	    //min_max_scanline(copie, &min, &max);
		//ei_edge_t ** tabaa = build_edge_table(copie,min,max);
		//print_edge_table(tabaa,min,max);
		
		
		ei_draw_polyline(main_window,copie,color2);
		hw_surface_unlock(main_window);
	    
	
	// Wait for a key press.
	event.type = ei_ev_none;
	while (event.type != ei_ev_keydown) {
		hw_event_wait_next(&event);
	}
	
	// Free hardware resources.
	while(copie!=NULL){
		
		ei_linked_point_t * c = copie;
		copie = copie->next;
		
		free(c);
	}
	copie = NULL;
	first = NULL;
	
	hw_quit();

	// Terminate program with no error code.
	return 0;
}
