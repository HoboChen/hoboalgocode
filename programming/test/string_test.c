#include <check.h>

#include <string/kmp.h>
#include <common/helper.h>

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

START_TEST (kmp_trival) {
    const char* p = "abcdabd";
    int* f = compute_prefix_function(p);
    int length = strlen(p);
    for (int i = 0; i < length; i++) {
        printf("%d ", f[i]);
    }
    printf("\n");
} END_TEST

Suite* swap_suite() {
    Suite *suite;
    TCase *test_case;

    suite = suite_create("Sort");
    test_case = tcase_create("Case0");
    tcase_add_test(test_case, kmp_trival);

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


