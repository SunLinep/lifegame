#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include "../lifegame.c"
#include "../lifegame.h"
#include "../sdlpart.h"

int suite_success_init(void){
    return 0;
}

int suite_success_clean(void){
    return 0;
}

void test_cell1(void){
    CU_ASSERT(cell(0, 3));
    CU_ASSERT(cell(1, 2));
    CU_ASSERT(cell(1, 3));
    CU_ASSERT_FALSE(cell(0, 1));
    CU_ASSERT_FALSE(cell(0, 5));
}

void test_cell2(void){
    CU_ASSERT_FALSE(cell(0, 1));
    CU_ASSERT_FALSE(cell(0, 5));
}

void test_init1(void){
    int* row;
    int* col;
    CU_ASSERT_EQUAL(init(row, col, "test1.txt"), 1);
    CU_ASSERT_EQUAL(*row, 3);
    CU_ASSERT_EQUAL(*col, 5);
}

void test_init2(void){
    int* row;
    int* col;
    CU_ASSERT_EQUAL(init(row, col, "test2.txt"), 1);
    CU_ASSERT_EQUAL(*row, 3);
    CU_ASSERT_EQUAL(*col, 5);
}

void test_init3(void){
    int* row;
    int* col;
    CU_ASSERT_EQUAL(init(row, col, "test7.txt"), 0);
}

void test_init4(void){
    int* row;
    int* col;
    CU_ASSERT_EQUAL(init(row, col, "test3.txt"), -1);
}

void test_init5(void){
    int* row;
    int* col;
    CU_ASSERT_EQUAL(init(row, col, "test4.txt"), -2);
    CU_ASSERT_EQUAL(init(row, col, "test5.txt"), -2);
    CU_ASSERT_EQUAL(init(row, col, "test6.txt"), -2);
}

void test_opt1(void){
    printf("\n");
    CU_ASSERT(opt());
}

CU_TestInfo test_cell[] = {
    {"cell_test1", test_cell1},
    {"cell_test2", test_cell2},
    CU_TEST_INFO_NULL
};

CU_TestInfo test_init[] = {
    {"init_test1", test_init1},
    {"init_test2", test_init2},
    {"init_test3", test_init3},
    {"init_test4", test_init4},
    {"init_test5", test_init5},
    CU_TEST_INFO_NULL
};

CU_TestInfo test_opt[] = {
    {"cell_test1", test_opt1},
    CU_TEST_INFO_NULL
};

CU_SuiteInfo suites[] = {
    {"test_cases1:", suite_success_init, suite_success_clean, NULL, NULL, test_cell},
    {"test_cases2:", suite_success_init, suite_success_clean, NULL, NULL, test_init},
    {"test_cases3:", suite_success_init, suite_success_clean, NULL, NULL, test_opt},
    CU_TEST_INFO_NULL
};

int main(void){
    if(CU_initialize_registry()) {
        fprintf(stderr, "Initialization of Test Registry faild. ");
        exit(EXIT_FAILURE);
    }else {
        assert(NULL != CU_get_registry());
        assert(!CU_is_test_running());
        if(CUE_SUCCESS != CU_register_suites(suites)){
            exit(EXIT_FAILURE);
        }
        CU_basic_set_mode(CU_BRM_VERBOSE);
        CU_basic_run_tests();        
    }
}

