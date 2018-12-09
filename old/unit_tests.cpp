#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "ei_draw.h"
#include "ei_main.h"
#include "hw_interface.h"
#include <stdbool.h>

TEST_CASE("create_window", "[unit]")
{
  //ENVIRONNEMENT Variables
  ei_surface_t main_window = NULL;
  ei_size_t main_window_size;
  main_window_size.width = 640;
  main_window_size.height = 480;
  // Position & color of the tested pixel
  ei_point_t test_point ={ 10 , 10 };
  ei_color_t test_color = {0,75,74,73};
  //Create window & check if worked well
  main_window = hw_create_window(&main_window_size, EI_FALSE);
  REQUIRE( main_window != NULL );
  //VERIFY SIZE WINDOW

  ei_size_t verifsize = hw_surface_get_size(main_window);
  REQUIRE( verifsize.width == main_window_size.width);
  REQUIRE( verifsize.height == main_window_size.height);

   //VERIFY PIXEL COLOR
   
   hw_surface_lock(main_window); //Gains exclusive access to a surface. Every call to hw_surface_lock must be matched by a call to hw_surface_unlock. 
   hw_put_pixel(main_window, test_point, test_color);
   hw_get_pixel(main_window, test_point);

   REQUIRE( (test_color.red == 0 && test_color.green == 75 && test_color.blue == 74 && test_color.alpha == 73 ));
   hw_surface_unlock(main_window);

  


}

TEST_CASE("TEST 3.2 surface_color red" , "[unit]"){
    //ENVIRONNEMENT Variables
    ei_surface_t main_windowb = NULL;
    ei_size_t main_windowb_size;
    main_windowb_size.width = 300;
    main_windowb_size.height = 300;

    main_windowb = hw_create_window(&main_windowb_size, EI_FALSE);
    REQUIRE( main_windowb != NULL );
    // Position & color of the tested pixel
    ei_color_t color = { 255, 0 , 0 ,255};  // RED
    ei_fill(main_windowb,&color,EI_TRUE);
    bool test_color_bool =true;
    ei_point_t pos ={0,0};
    for (pos.x =0 ; pos.y < main_windowb_size.width; pos.x++) {
        for (pos.y=0 ; pos.y < main_windowb_size.height; pos.y++){
             ei_color_t test_color = hw_get_pixel(main_windowb, pos);
             if (!(test_color.red == 255 && test_color.green == 0 && test_color.blue == 0 && test_color.alpha == 255 )){
                 test_color_bool=false;

             }

            }
        }
    REQUIRE(test_color_bool);

   
}

TEST_CASE("TEST 4.2 surface_color GREEN copy on main window" , "[unit]"){

 //ENVIRONNEMENT Variables
    ei_surface_t main_window2 = NULL;
    ei_size_t main_window2_size;
    main_window2_size.width = 640;
    main_window2_size.height = 480;

    main_window2 = hw_create_window(&main_window2_size, EI_FALSE);
    REQUIRE( main_window2 != NULL );
    bool test_color_bool2 =true;

    // Create the source surface.
    ei_surface_t source_surface = NULL;
    ei_size_t    source_surface_size;
    source_surface_size.width	= 300;
    source_surface_size.height	= 300;
    source_surface = hw_surface_create(main_window2, &source_surface_size);

//Fill the source surface by color GREEN & copy it on  main_window 
    ei_color_t color = { 0,255,0,255};
    ei_fill(source_surface,&color,EI_FALSE);
    ei_point_t pos_surface = {60,100};
    ei_copy_surface(main_window2,source_surface,&pos_surface,EI_FALSE);



    ei_point_t surface_used_green=pos_surface;
    surface_used_green.x += source_surface_size.width;
    surface_used_green.y += source_surface_size.height;

    //CHECK ALL PIXELS OF MAIN WINDOW 1st STEP GREEN SURFACE
    for (int i = pos_surface.x ; i < surface_used_green.x; i++) {
        for (int j = pos_surface.y ; j < surface_used_green.y ; j++){
             ei_point_t pos ={i,j};
             ei_color_t test_color2 = hw_get_pixel(main_window2, pos);

             if (!(test_color2.red == 0 && test_color2.green == 255 && test_color2.blue == 0 && test_color2.alpha == 255 ))
                 test_color_bool2=false;


        }

}
     REQUIRE(test_color_bool2);
    //CHECK ALL PIXELS OF MAIN WINDOW 2 STEP OTHER PIXELS
    for (int i =surface_used_green.x ; i < main_window2_size.width ; i++) {
        for (int j =surface_used_green.y ; j < main_window2_size.height ; j++){
             ei_point_t pos ={i,j};
             ei_color_t test_color3 = hw_get_pixel(main_window2, pos);

             if (test_color3.red == 0 && test_color3.green == 255 && test_color3.blue == 0 && test_color3.alpha == 255 )
                 test_color_bool2=false;


        }

}
    REQUIRE(test_color_bool2);

}


int ei_main(int argc, char* argv[])
{
  // Init acces to hardware.
  hw_init();

  int result = Catch::Session().run( argc, argv );

  // Free hardware resources.
  hw_quit();

  return result;
}
