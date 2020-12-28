#include <CUnit/CUnit.h>
#include <assert.h>
#include "common.h"

void sanity_check() {
   CU_ASSERT(1);
}

CU_TestInfo cases[] = {
        {"Sanity Check:", sanity_check},
        CU_TEST_INFO_NULL
};


CU_SuiteInfo suites[] = {
        {"Sanity Check Suite:", init, clean, NULL, NULL, cases},
        CU_SUITE_INFO_NULL
};

int register_sanity_suite() {
    assert(CU_get_registry());
    assert(!CU_is_test_running());

    CU_register_suites(suites);
    return CU_get_error();
}