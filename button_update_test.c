#include <stdio.h>
#include <assert.h>
#include "button_update.h"

void test_short_press()
{
    for (int i = 0; i < BUTTON_SHORT_PRESS_COUNT; i++)
    {
        assert(button_update(1) == BUTTON_NONE);
    }
    assert(button_update(0) == BUTTON_1);
}

void test_short_noise()
{
    for (int i = 0; i < (BUTTON_SHORT_PRESS_COUNT/2); i++)
    {
        assert(button_update(1) == BUTTON_NONE);
    }
    assert(button_update(0) == BUTTON_NONE);
}


typedef void (*test_func)(void);

const test_func test_functions[] = {
    test_short_press,
    test_short_noise
};
extern unsigned char button_1_loop;

int main()
{
    const int test_count = sizeof(test_functions)/sizeof(test_func);

    for (int i = 0; i < test_count; i++)
    {
        // reset states
        button_1_loop = 0;

        test_functions[i]();
    }


    return 0;
}
