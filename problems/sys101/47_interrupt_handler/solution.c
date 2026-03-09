/**
 * Problem 47: Interrupt Handler
 * IRQ handling and interrupt dispatch.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IRQ 32

typedef void (*IRQHandler)(int);

typedef struct {
    IRQHandler handler;
    int priority;
    int count;
} IRQEntry;

typedef struct {
    IRQEntry irqs[MAX_IRQ];
    uint32_t pending;
} InterruptController;

InterruptController* irq_init() {
    InterruptController* ic = calloc(1, sizeof(InterruptController));
    printf("IRQ controller initialized\n");
    return ic;
}

void irq_register(InterruptController* ic, int irq, IRQHandler handler, int prio) {
    ic->irqs[irq].handler = handler;
    ic->irqs[irq].priority = prio;
    printf("Registered IRQ %d\n", irq);
}

void irq_raise(InterruptController* ic, int irq) {
    ic->pending |= (1 << irq);
    printf("IRQ %d raised\n", irq);
}

void timer_handler(int irq) { printf("  Timer IRQ %d\n", irq); }

int main() {
    printf("=== Interrupt Handler ===\n\n");
    InterruptController* ic = irq_init();
    irq_register(ic, 0, timer_handler, 10);
    irq_raise(ic, 0);
    if (ic->irqs[0].handler) ic->irqs[0].handler(0);
    free(ic);
    return 0;
}