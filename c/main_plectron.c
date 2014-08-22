#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "plectron.h"

int main() {
    int i;
    const uint8_t salt[16] = {
        0x4c, 0x88, 0x0a, 0xa5, 0x53, 0x66, 0x9c, 0x38,
        0x69, 0xf6, 0x2b, 0x38, 0x9c, 0x2c, 0x34, 0x99,
    };
    const char *password = "The quick brown fox jumps over the lazy dog";
    uint8_t tag[32] = {0};
    int error_code;

    printf("salt in hex: ");
    for (i = 0; i < 16; i++) {
        printf("%02x", salt[i]);
    }
    printf("\n");

    printf("password: %s\n", password);

    clock_t begin, end;
    double time_spent;
    begin = clock();
    for (int i = 0; i < 1000; i++) {
        error_code = plectron(
                tag, 256,
                salt,
                (const uint8_t *)password, 8 * strlen(password),
                1, 65536  // tcost, mcost
                // 2, 1024  // tcost, mcost
        );
    }
    end = clock();
    time_spent = ((double)(end - begin)) / CLOCKS_PER_SEC;

    if (0 == error_code) {
        printf("digest in hex: ");
        for (i = 0; i < 32; i++) {
            printf("%02x", tag[i]);
        }
        printf("\n");

    } else {
        printf("Error code: %d\n", error_code);
    }

    printf("used time: %f seconds\n", time_spent);

    return 0;
}
