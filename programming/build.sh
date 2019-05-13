mkdir -p build/
gcc test/swap_test.c -o build/swap_test -Isrc/ -pthread -lcheck_pic -pthread -lrt -lm -lsubunit -std=c11
gcc test/sort_test.c -o build/sort_test -Isrc/ -pthread -lcheck_pic -pthread -lrt -lm -lsubunit -std=c11
