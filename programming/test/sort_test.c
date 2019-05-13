#include <check.h>

#include <sort/quick_sort.h>
#include <sort/merge_sort.h>
#include <sort/insertation_sort.h>
#include <common/helper.h>

#include <stdlib.h>
#include <assert.h>
#include <time.h>

START_TEST (quick_sort_trival) {
    static_assert(RAND_MAX >= 32767, "Not ISO C");
    srand(time(0));

    int length = 20;
    int a[length];
    for (int i = 0; i < length; i++) {
        a[i] = rand() % 1000;
    }

    quick_sort(a, 0, length - 1);

    ck_assert(is_ascending_order(a, 0, length - 1));
} END_TEST

START_TEST (merge_sort_trival) {
    static_assert(RAND_MAX >= 32767, "Not ISO C");
    srand(time(0));

    int length = 20;
    int a[length];
    for (int i = 0; i < length; i++) {
        a[i] = rand() % 1000;
    }
    for (int i = 0; i < length; i++) {
        printf("%d ", a[i]);
    }

    printf("\n");


    merge_sort(a, 0, length - 1);
    for (int i = 0; i < length; i++) {
        printf("%d ", a[i]);
    }
    // ck_assert(is_ascending_order(a, 0, length - 1));
} END_TEST

START_TEST (insertation_sort_trival) {
    static_assert(RAND_MAX >= 32767, "Not ISO C");
    srand(time(0));

    int length = 20;
    int a[length];
    for (int i = 0; i < length; i++) {
        a[i] = rand() % 1000;
    }
    for (int i = 0; i < length; i++) {
        printf("%d ", a[i]);
    }

    printf("\n");


    insertation_sort(a, 0, length - 1);
    for (int i = 0; i < length; i++) {
        printf("%d ", a[i]);
    }
    ck_assert(is_ascending_order(a, 0, length - 1));
} END_TEST


Suite* swap_suite() {
    Suite *suite;
    TCase *test_case;

    suite = suite_create("Sort");
    test_case = tcase_create("Case0");
    tcase_add_test(test_case, quick_sort_trival);
    tcase_add_test(test_case, merge_sort_trival);
    tcase_add_test(test_case, insertation_sort_trival);

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


