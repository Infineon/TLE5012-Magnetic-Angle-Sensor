// test includes
#include "Test_includes.hpp"


extern "C" {
    // project includes
    #include "Test_TLx5012B_REG_needsSensor.h"
    #include "Test_TLx5012B_commonFunctions_needsSensor.h"


    // Method invoked by Unity before a test suite is run
    void TLx5012B_REG_needsSensor_suiteSetup() {
        // // deinit in TEAR_DOWN will cut communication link, so if deinit is called communication must be reinitialized !
        // (void) TLx5012B_P3B6_init(&dut);
        // bsc.setPowerPin(POWER_PIN, OUTPUT, INPUT, HIGH, LOW, 0, 250000);
        // ifx::TLx5012B::initBoardSupport(&dut, bsc);
        // bsc.init();
        // // ifx::TLx5012B::initCommunication(&dut, Wire, TLx5012B_IIC_ADDR_A0_e, true);
        // ifx::TLx5012B::initCommunication(&dut, Wire, TLx5012B_IIC_ADDR_A1_e, true);
        // dut.functions->setDefaultConfig(&dut);
    }

    // Method invoked by Unity after a test suite is run
    void TLx5012B_REG_needsSensor_suiteTearDown() {
        // ifx::TLx5012B::deinitCommunication(&dut, true);
        // bsc.deinit();
        // // If deinitializing here make sure to reinit in 'TEST_SETUP' or communication will be lost !
        // dut.functions->deinit(&dut);
    }

}
