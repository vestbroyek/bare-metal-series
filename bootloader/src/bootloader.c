#include "common-defines.h"

#include <libopencm3/stm32/memorymap.h>

#define BOOTLOADER_SIZE (0x8000U)
#define MAIN_APP_START_ADDRESS (FLASH_BASE + BOOTLOADER_SIZE)

static void jump_to_main(void) {
    typedef void (*void_fn)(void); // typedef for a void func

    // Get pointer to reset handler's address
    uint32_t* reset_vector_entry = (uint32_t*)(MAIN_APP_START_ADDRESS + 4U);

    // Dereference to get callable at address
    uint32_t* reset_vector = (uint32_t*)(*reset_vector_entry);

    // Cast to func
    void_fn jump_fn = (void_fn)reset_vector;

    jump_fn();

}

int main(void) {
    jump_to_main();

    // Never returns
    return 0;
}