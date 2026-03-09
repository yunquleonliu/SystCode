#include <stdio.h>

typedef void (*IsrHandler)(void);

enum { VECTOR_COUNT = 8 };

static int g_events = 0;

static void default_handler(void) {
    g_events += 1;
}

static void timer_handler(void) {
    g_events += 10;
}

static void uart_handler(void) {
    g_events += 100;
}

static void vector_invoke(IsrHandler* table, int irq) {
    if (irq >= 0 && irq < VECTOR_COUNT && table[irq] != NULL) {
        table[irq]();
    }
}

int main(void) {
    IsrHandler flash_vector[VECTOR_COUNT];
    IsrHandler ram_vector[VECTOR_COUNT];

    for (int index = 0; index < VECTOR_COUNT; ++index) {
        flash_vector[index] = default_handler;
        ram_vector[index] = default_handler;
    }

    flash_vector[3] = timer_handler;
    flash_vector[4] = uart_handler;

    for (int index = 0; index < VECTOR_COUNT; ++index) {
        ram_vector[index] = flash_vector[index];
    }

    vector_invoke(ram_vector, 3);
    vector_invoke(ram_vector, 4);
    vector_invoke(ram_vector, 7);

    int ok = (g_events == 111);
    printf("[E010] events=%d %s\n", g_events, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
