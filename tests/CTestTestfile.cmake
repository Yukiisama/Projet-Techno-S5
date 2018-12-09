# CMake generated Testfile for 
# Source directory: /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests
# Build directory: /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test("create_window" "/net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests/unit_tests" "create_window" "--durations" "yes" "--warn" "NoAssertions" "--name" "unit_tests ( build)")
set_tests_properties("create_window" PROPERTIES  FAIL_REGULAR_EXPRESSION "No tests ran" LABELS ";unit;" TIMEOUT "10")
