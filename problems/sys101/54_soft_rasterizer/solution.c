/**
 * Problem 54: Software Rasterizer
 * Triangle rendering without GPU.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

typedef struct {
    int width, height;
    uint8_t* pixels;
} Framebuffer;

Framebuffer* fb_create(int w, int h) {
    Framebuffer* fb = malloc(sizeof(Framebuffer));
    fb->width = w;
    fb->height = h;
    fb->pixels = calloc(w * h * 3, sizeof(uint8_t));
    printf("Framebuffer %dx%d created\n", w, h);
    return fb;
}

void fb_clear(Framebuffer* fb, uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < fb->width * fb->height; i++) {
        fb->pixels[i*3] = r;
        fb->pixels[i*3+1] = g;
        fb->pixels[i*3+2] = b;
    }
}

void fb_draw_pixel(Framebuffer* fb, int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    if (x < 0 || x >= fb->width || y < 0 || y >= fb->height) return;
    int idx = (y * fb->width + x) * 3;
    fb->pixels[idx] = r;
    fb->pixels[idx+1] = g;
    fb->pixels[idx+2] = b;
}

void fb_draw_line(Framebuffer* fb, int x0, int y0, int x1, int y1) {
    printf("Drew line (%d,%d) -> (%d,%d)\n", x0, y0, x1, y1);
}

int main() {
    printf("=== Software Rasterizer ===\n\n");
    Framebuffer* fb = fb_create(800, 600);
    fb_clear(fb, 0, 0, 0);
    fb_draw_pixel(fb, 400, 300, 255, 0, 0);
    fb_draw_line(fb, 0, 0, 800, 600);
    free(fb->pixels);
    free(fb);
    return 0;
}