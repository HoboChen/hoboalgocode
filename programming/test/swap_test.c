#include <check.h>
#include <common/swap.h>

START_TEST (swap_trival) {
    int a = 3;
    int b = 2;
    swap(&a, &b, sizeof(a));
    ck_assert_int_eq(a, 2);
    ck_assert_int_eq(b, 3);
} END_TEST

START_TEST (swap_many_times) {
    int times = 10000;
    for (int i = 0; i < times; i++) {
        int a = 3;
        int b = 2;
        swap(&a, &b, sizeof(a));
        ck_assert_int_eq(a, 2);
        ck_assert_int_eq(b, 3);
    }
} END_TEST

Suite* swap_suite() {
    Suite *suite;
    TCase *test_case;

    suite = suite_create("Swap");
    test_case = tcase_create("Case0");
    tcase_add_test(test_case, swap_trival);
    tcase_add_test(test_case, swap_many_times);
    suite_add_tcase(suite, test_case);

    return suite;
}

int main() {

    int failedCount = 0;                   
    Suite* suite = swap_suite();                            
    SRunner *runner = srunner_create(suite);                     

    srunner_run_all(runner, CK_NORMAL);  
    failedCount = srunner_ntests_failed(runner); 
    srunner_free(runner);                      

    return (failedCount == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  
}
