#include <stdlib.h>
#include "ei_event.h"
#include "hw_interface.h"
#include <stdio.h>
#include <stdbool.h>
#include "ei_draw.h"

//Colors for terminal
#define BLUE   "\x1B[34m"
#define BOLDRED     "\033[1m\033[31m"
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

    // BEGINNING TP1

    printf(GREEN "BEGIN OF TP1 \nWidth of the window is %d  ; Height of the window is %d\n" RESET, main_window_size.width , main_window_size.height);

    //Get pixel to change afterwards

    ei_point_t pos_TP1 = { 10 , 20 } ;
    ei_color_t color_TP1 =hw_get_pixel(main_window,pos_TP1);
    ei_color_t new_color = {0,0,255,255}; // BLUE COLOR

    //Verify pixel & change color
    printf ( "Check color pixel at position (10 ,20 ) before turning blue \n");
    printf( YELLOW "Blue %d | alpha %d | green %d | red %d\n" RESET ,(int) color_TP1.blue , (int) color_TP1.alpha , (int) color_TP1.green , (int) color_TP1.red);

    //Gains exclusive access to a surface. Every call to hw_surface_lock must be matched by a call to hw_surface_unlock.
    hw_surface_lock(main_window);

    //Put new pixel color
    hw_put_pixel(main_window,pos_TP1,new_color);
    color_TP1 = hw_get_pixel(main_window,pos_TP1);

    //Last check up new color pixel /!\ blue
    printf ( "Check color pixel at position (10 ,20 ) after turning blue \n");
    printf( BLUE "Blue %d  |  alpha %d | green %d | red %d\n " YELLOW"END TP1 ! BEGIN OF TP2 \n" RESET ,(int) color_TP1.blue , (int) color_TP1.alpha , (int) color_TP1.green , (int) color_TP1.red);

    //END TP1





    //Fill the main_window by color RED
    ei_color_t color = { 255,0,0,255};
    ei_fill(main_window,&color,EI_FALSE);


    //4.1 Green surface 300x300 GREEN POS (60,100)

    // Create the source surface.
    ei_surface_t source_surface = NULL;
    ei_size_t    source_surface_size;
    source_surface_size.width	= 300;
    source_surface_size.height	= 300;
    source_surface = hw_surface_create(main_window, &source_surface_size);

    //Fill the main_window by color GREEN & copy it on source surface
    ei_color_t color2 = { 0,255,0,255};
    ei_fill(source_surface,&color2,EI_FALSE);

    ei_point_t pos_surface = {60,100};
    ei_copy_surface(main_window,source_surface,&pos_surface,EI_FALSE);


    //6) DRAW SOME TEXT
    static const int ei_font_default_size = 42;  ///< Default font color
    static const char ei_default_font_filename[] = DATA_DIR"font.ttf";
    ei_font_t Font = hw_text_font_create(ei_default_font_filename,ei_font_default_size);
    const char * text = "Test text";
    ei_point_t pos_text = {10,10};
    ei_color_t color_text = {0,0,255,255};


    // Apply draw text and update the surfaces.
    ei_draw_text(source_surface,&pos_text,text,Font,&color_text);
    ei_copy_surface(main_window,source_surface,&pos_surface,EI_TRUE);




    //3.3 Read image in argument
    //position of the image we need to copy on the main surface
    ei_point_t pos = {50,100};

    if (argc==2){

        //prefix the access path to the name of the picture
        char chaine [100];
        sprintf(chaine , "%s%s",DATA_DIR,argv[1]);

        //LOADING & COPY
        ei_surface_t source = hw_image_load(chaine);

        if (source!= NULL)
            ei_copy_surface(main_window,source,&pos,EI_TRUE);
        else
            fprintf(stderr," Wrong path image \n");
    }


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
