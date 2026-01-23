/**
 * Problem 59: Rotary Encoder Input
 * Quadrature encoded rotary input handling.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int channel_a;
    int channel_b;
    int position;
    int direction;  // 1=CW, -1=CCW
} RotaryEncoder;

RotaryEncoder* encoder_init() {
    RotaryEncoder* enc = calloc(1, sizeof(RotaryEncoder));
    enc->channel_a = 0;
    enc->channel_b = 0;
    enc->position = 0;
    printf("Rotary encoder initialized\n");
    return enc;
}

void encoder_update(RotaryEncoder* enc, int a, int b) {
    int old_a = enc->channel_a;
    enc->channel_a = a;
    enc->channel_b = b;
    
    if (old_a != a) {
        if (a == b) {
            enc->position++;
            enc->direction = 1;
            printf("Clockwise: position=%d\n", enc->position);
        } else {
            enc->position--;
            enc->direction = -1;
            printf("Counter-clockwise: position=%d\n", enc->position);
        }
    }
}

int main() {
    printf("=== Rotary Encoder ===\n\n");
    RotaryEncoder* enc = encoder_init();
    
    encoder_update(enc, 1, 0);  // CW
    encoder_update(enc, 1, 1);  // CW
    encoder_update(enc, 0, 1);  // CW
    encoder_update(enc, 0, 0);  // CW
    
    printf("Final position: %d\n", enc->position);
    free(enc);
    return 0;
}