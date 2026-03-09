#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

static int sum_variadic(int count, ...) {
    va_list args;
    va_start(args, count);
    int total = 0;
    for (int index = 0; index < count; ++index) {
        total += va_arg(args, int);
    }
    va_end(args);
    return total;
}

static uintptr_t current_frame(void) {
#if defined(__GNUC__) || defined(__clang__)
    return (uintptr_t)__builtin_frame_address(0);
#else
    return 0u;
#endif
}

int main(void) {
    int total = sum_variadic(5, 1, 2, 3, 4, 5);
    uintptr_t frame = current_frame();
    int ok = (total == 15);

    printf("[E009] variadic_sum=%d frame=0x%zx %s\n", total, (size_t)frame, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
