#include "CUnit.h"
#include "Basic.h"

#include "dangerDetection.h"

/* Test Suite setup and cleanup functions: */

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

void cdb_test()
{
    double value[2] = {1234.12, 12821.8123};
    double *tmp = chassis_domain_bus(2, value[0], value[1] );
    for (int i = 0; i < (sizeof tmp / sizeof tmp[0]) ; i++)
    {
        CU_ASSERT_EQUAL(tmp[i],value[i]);
    }
}

int main ( void )
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if ( CUE_SUCCESS != CU_initialize_registry() )
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite( "max_test_suite", init_suite, clean_suite );
   if ( NULL == pSuite ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ( (NULL == CU_add_test(pSuite, "cdb_test", cdb_test))
      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // Run all tests using the basic interface
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");
    /*
   // Run all tests using the automated interface
   CU_automated_run_tests();
   CU_list_tests_to_file();

   // Run all tests using the console interface
   CU_console_run_tests();
    */
   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}