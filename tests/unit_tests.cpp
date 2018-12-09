#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "ei_main.h"
#include "hw_interface.h"

TEST_CASE("create_window", "[unit]")
{
  ei_surface_t main_window = NULL;
  ei_size_t main_window_size;
  main_window_size.width = 640;
  main_window_size.height = 480;

  main_window = hw_create_window(&main_window_size, EI_FALSE);
  REQUIRE( main_window != NULL );
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