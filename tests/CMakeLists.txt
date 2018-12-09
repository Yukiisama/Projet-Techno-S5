# tp1 target
add_executable(tp1 tp1.c)
target_link_libraries(tp1 eibase ${Allegro_LIBRARIES} m)

# tp3 target
add_executable(tp3c tp3_correction.c)
target_link_libraries(tp3c ei eibase ${Allegro_LIBRARIES} m)

# tp4 target
add_executable(tp4 tp4.c)
target_link_libraries(tp4 ei eibase ${Allegro_LIBRARIES} m)
link_libraries(m)

add_executable(tp4_button tp4_button.c)
target_link_libraries(tp4_button ei eibase ${Allegro_LIBRARIES} m)
link_libraries(m)

# tp5 target
add_executable(tp5 tp5.c)
target_link_libraries(tp5 ei eibase ${Allegro_LIBRARIES} m)
link_libraries(m)

# tp5 target
#add_executable(tp5_correc tp5_correction.c)
#target_link_libraries(tp5 ei eibase ${Allegro_LIBRARIES} m)
#link_libraries(m)
# tp6 target
add_executable(tp6 tp6.cpp viewer.cpp viewer.h Rectangle.cpp Rectangle.h Point.cpp Point.h Shape.cpp Shape.h Square.cpp Square.h)
target_link_libraries(tp6 ei eibase ${Allegro_LIBRARIES} m)

# Automatic tests
add_executable(unit_tests unit_tests.cpp)
target_link_libraries(unit_tests ei eibase ${Allegro_LIBRARIES} m)

enable_testing()
ms_add_catch_tests(unit_tests) 
 

