#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define PAINT_PATTERN 0xA5u

static void stack_paint(uint8_t* memory, size_t size) {
    memset(memory, PAINT_PATTERN, size);
}

static void simulate_stack_usage(uint8_t* memory, size_t size, size_t used) {
    if (used > size) {
        used = size;
    }
    for (size_t index = 0; index < used; ++index) {
        memory[size - 1u - index] = (uint8_t)(index & 0xFFu);
    }
}

static size_t stack_high_watermark(const uint8_t* memory, size_t size) {
    size_t untouched = 0;
    for (size_t index = 0; index < size; ++index) {
        if (memory[index] == PAINT_PATTERN) {
            ++untouched;
        } else {
            break;
        }
    }
    return size - untouched;
}

int main(void) {
    uint8_t fake_stack[256];
    stack_paint(fake_stack, sizeof(fake_stack));
    simulate_stack_usage(fake_stack, sizeof(fake_stack), 96);

    size_t used = stack_high_watermark(fake_stack, sizeof(fake_stack));
    int ok = (used == 96u);
    printf("[E006] used=%zu bytes %s\n", used, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
