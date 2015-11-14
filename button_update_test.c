#include <stdio.h>
#include <assert.h>
#include "button_update.h"

#define TEST_BUTTON_STATE_LOOP(btn, count, result) \
{ \
    for (int i = 0; i < (count); i++) \
        assert(button_update(btn) == (result)); \
}

void test_short_press()
{
    TEST_BUTTON_STATE_LOOP(0, 100, BUTTON_NONE);
    TEST_BUTTON_STATE_LOOP(1, BUTTON_SHORT_PRESS_COUNT - 1, BUTTON_NONE);
    TEST_BUTTON_STATE_LOOP(1, 1, BUTTON_1);
    TEST_BUTTON_STATE_LOOP(1, 1, BUTTON_NONE);
}

void test_short_noise()
{
    TEST_BUTTON_STATE_LOOP(1, BUTTON_SHORT_PRESS_COUNT / 2, BUTTON_NONE);
    TEST_BUTTON_STATE_LOOP(0, 1, BUTTON_NONE);
}

void test_short_press_continue_to_press()
{
    TEST_BUTTON_STATE_LOOP(1, BUTTON_SHORT_PRESS_COUNT - 1, BUTTON_NONE);
    TEST_BUTTON_STATE_LOOP(1, 1, BUTTON_1);
    TEST_BUTTON_STATE_LOOP(1, 1000, BUTTON_NONE);
}

void test_short_press_continue_to_press_with_noise()
{
    TEST_BUTTON_STATE_LOOP(1, BUTTON_SHORT_PRESS_COUNT - 1, BUTTON_NONE);
    TEST_BUTTON_STATE_LOOP(1, 1, BUTTON_1);
    TEST_BUTTON_STATE_LOOP(1, 1000, BUTTON_NONE);
    TEST_BUTTON_STATE_LOOP(0, BUTTON_DEASSERT_COUNT / 2, BUTTON_NONE);
    TEST_BUTTON_STATE_LOOP(1, 1000, BUTTON_NONE);
}

void test_2_short_press()
{
    TEST_BUTTON_STATE_LOOP(1, BUTTON_SHORT_PRESS_COUNT - 1, BUTTON_NONE);
    TEST_BUTTON_STATE_LOOP(1, 1, BUTTON_1);
    TEST_BUTTON_STATE_LOOP(0, BUTTON_DEASSERT_COUNT, BUTTON_NONE);
    TEST_BUTTON_STATE_LOOP(1, BUTTON_SHORT_PRESS_COUNT - 1, BUTTON_NONE);
    TEST_BUTTON_STATE_LOOP(1, 1, BUTTON_1);
    TEST_BUTTON_STATE_LOOP(1, 1000, BUTTON_NONE);
}

void test_2_short_press_with_long_release()
{
    TEST_BUTTON_STATE_LOOP(1, BUTTON_SHORT_PRESS_COUNT - 1, BUTTON_NONE);
    TEST_BUTTON_STATE_LOOP(1, 1, BUTTON_1);
    TEST_BUTTON_STATE_LOOP(0, BUTTON_DEASSERT_COUNT * 10, BUTTON_NONE);
    TEST_BUTTON_STATE_LOOP(1, BUTTON_SHORT_PRESS_COUNT - 1, BUTTON_NONE);
    TEST_BUTTON_STATE_LOOP(1, 1, BUTTON_1);
    TEST_BUTTON_STATE_LOOP(1, 1000, BUTTON_NONE);
}


typedef void (*test_func)(void);

const test_func test_functions[] = {
    test_short_press,
    test_short_noise,
    test_short_press_continue_to_press,
    test_short_press_continue_to_press_with_noise,
    test_2_short_press,
    test_2_short_press_with_long_release
};

extern unsigned char button_1_loop;
extern unsigned char button_1_state;

int main()
{
    const int test_count = sizeof(test_functions)/sizeof(test_func);

    for (int i = 0; i < test_count; i++)
    {
        //puts(".");
        // reset states
        button_1_loop = 0;
        button_1_state = 0;

        test_functions[i]();
    }


    return 0;
}
