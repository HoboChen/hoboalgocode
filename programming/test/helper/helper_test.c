#include <check.h>
#include <helper/swap.h>

START_TEST (SwapTrival) {
    int a = 3;
    int b = 2;
    swap(&a, &b, sizeof(a));
    ck_assert_int_eq(a, 2);
    ck_assert_int_eq(b, 3);
} END_TEST

START_TEST (SwapManyTimes) {
    int times = 10000;
    for (int i = 0; i < times; i++) {
        int a = 3;
        int b = 2;
        swap(&a, &b, sizeof(a));
        ck_assert_int_eq(a, 2);
        ck_assert_int_eq(b, 3);
    }
} END_TEST

Suite* SwapSuite() {
    Suite *suite;
    TCase *testCase;

    suite = suite_create("Swap");
    testCase = tcase_create("Trival");
    tcase_add_test(testCase, SwapTrival);
    tcase_add_test(testCase, SwapManyTimes);
    suite_add_tcase(suite, testCase);

    return suite;
}

int main(void) {
    int failedCount = 0;                   
    Suite* swapSuite = SwapSuite();                            
    SRunner *runner = srunner_create(swapSuite);                     

    srunner_run_all(runner, CK_NORMAL);  
    failedCount = srunner_ntests_failed(runner); 
    srunner_free(runner);                      

    return (failedCount == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  
}