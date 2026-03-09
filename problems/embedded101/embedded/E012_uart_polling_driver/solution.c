#include <stdio.h>
#include <string.h>

typedef struct {
    char tx_log[256];
    size_t tx_len;
    char rx_fifo[256];
    size_t rx_head;
    size_t rx_tail;
} Uart;

static void uart_init(Uart* uart) { memset(uart, 0, sizeof(*uart)); }
static void uart_polling_send(Uart* uart, const char* text) {
    while (*text != '\0' && uart->tx_len + 1 < sizeof(uart->tx_log)) {
        uart->tx_log[uart->tx_len++] = *text++;
    }
}
static int uart_polling_recv(Uart* uart, char* out) {
    if (uart->rx_head == uart->rx_tail) return 0;
    *out = uart->rx_fifo[uart->rx_head++];
    return 1;
}

int main(void) {
    Uart uart;
    uart_init(&uart);
    uart_polling_send(&uart, "HELLO");
    uart.rx_fifo[uart.rx_tail++] = 'O';
    uart.rx_fifo[uart.rx_tail++] = 'K';
    char first = '\0';
    char second = '\0';
    int got1 = uart_polling_recv(&uart, &first);
    int got2 = uart_polling_recv(&uart, &second);
    int ok = (uart.tx_len == 5u) && got1 && got2 && first == 'O' && second == 'K';
    printf("[E012] tx=%.*s rx=%c%c %s\n", (int)uart.tx_len, uart.tx_log, first, second, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
