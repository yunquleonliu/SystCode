#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint8_t tx_last;
    uint8_t rx_last;
} SpiMaster;

static uint8_t spi_transfer_byte(SpiMaster* spi, uint8_t tx) {
    spi->tx_last = tx;
    spi->rx_last = (uint8_t)(tx ^ 0xFFu);
    return spi->rx_last;
}

int main(void) {
    SpiMaster spi = {0};
    uint8_t rx0 = spi_transfer_byte(&spi, 0x55u);
    uint8_t rx1 = spi_transfer_byte(&spi, 0x0Fu);
    int ok = (rx0 == 0xAAu) && (rx1 == 0xF0u);
    printf("[E019] rx0=0x%02X rx1=0x%02X %s\n", rx0, rx1, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
