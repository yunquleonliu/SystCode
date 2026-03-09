#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint16_t sample;
} Adc;

static uint16_t adc_single_conversion(Adc* adc, uint16_t analog_input_mv) {
    if (analog_input_mv > 3300u) analog_input_mv = 3300u;
    adc->sample = (uint16_t)((analog_input_mv * 4095u) / 3300u);
    return adc->sample;
}

int main(void) {
    Adc adc = {0};
    uint16_t sample = adc_single_conversion(&adc, 1650u);
    int ok = (sample >= 2047u && sample <= 2048u);
    printf("[E020] sample=%u %s\n", sample, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
