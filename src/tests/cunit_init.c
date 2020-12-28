#include <CUnit/Basic.h>

extern int register_sanity_suite();

int main() {
   if (CU_initialize_registry()) {
      fprintf(stderr, "Error while initializing CUnit: %s", CU_get_error_msg());
      return CU_get_error();
   }

   register_sanity_suite();

   CU_basic_run_tests();
   CU_cleanup_registry();   
   return CU_get_error();
}
