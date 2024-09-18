// test includes
#include "Test_includes.hpp"


extern "C" {
    /***
      * Uses flags / defines to determine which groups of tests should be added to this test such that multiple tests can be executed in a single run.
      * Use the '--build-property option of the 'arduino_compile' target to add the flags by defining the respective targets in the makefile.
      * makefile : --build-property "compiler.cpp.extra_flags=\"-D<TEST_SPECIFIER>=1\"" build
    */
    void RunAllTests(void)
    {

// TLx512B_REG register tests
#ifdef TEST_TLx5012B_REG

     RUN_TEST_GROUP(TLx5012B_REG);

#endif

#ifdef TEST_TLx5012B_REG_NEEDS_SENSOR

     RUN_TEST_GROUP(TLx5012B_REG_needsSensor);

#endif

    }
}


/***
 * 
*/
void setup() {
    Serial.begin(115200);
    delay(3000);

    Serial.print("setup done.\n");
}


/***
 *
*/
void loop() {
    Serial.println("\n");

    const int   argc       = 2;
    const char *argv[argc] = { "", "-v" };

    (void) UnityMain(argc, argv, RunAllTests);
    delay(3000);
}