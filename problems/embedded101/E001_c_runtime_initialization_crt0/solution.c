#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    uint32_t sidata[4];
    uint32_t sdata[4];
    uint32_t sbss[6];
} MemoryImage;

static void reset_handler_init(MemoryImage* image) {
    memcpy(image->sdata, image->sidata, sizeof(image->sdata));
    memset(image->sbss, 0, sizeof(image->sbss));
}

int main(void) {
    MemoryImage image = {
        .sidata = {0xCAFEBABE, 0x0000002A, 0x12345678, 0x0BADF00D},
        .sdata = {0, 0, 0, 0},
        .sbss = {1, 2, 3, 4, 5, 6}
    };

    reset_handler_init(&image);

    int ok_data = memcmp(image.sdata, image.sidata, sizeof(image.sdata)) == 0;
    int ok_bss = 1;
    for (size_t index = 0; index < sizeof(image.sbss) / sizeof(image.sbss[0]); ++index) {
        if (image.sbss[index] != 0) {
            ok_bss = 0;
            break;
        }
    }

    printf("[E001] data_copy=%s bss_zero=%s\n", ok_data ? "PASS" : "FAIL", ok_bss ? "PASS" : "FAIL");
    return (ok_data && ok_bss) ? 0 : 1;
}
