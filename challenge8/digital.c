#include "digital.h"

int main(int argc, char** argv) {
    char file[15002];
    read(STDIN_FILENO, file, 15001);

    char image[sizeof(Layer)];
    for (int i = 0; i < sizeof(Layer); i++) image[i] = '2';

    for (int layer = 0; layer < 100; layer++) {
        for (int i = 0; i < sizeof(Layer); i++) {
            if (image[i] == '2') {
                image[i] = file[layer*sizeof(Layer) + i];
            }
        }
    }

    for (int i = 0; i < sizeof(Layer); i++) {
        printf("%c", image[i]);
        if ((i+1)%25 == 0) printf("\n");
    }

    return 0;
}

// 0 is black, 1 is white, and 2 is transparent.
// Algorithm: read each layr (starting with top layer)
// * If there's a pixel there already, continue
// * If there's not yet, then add this. (unless it's 2)
//
// Answer:
// 1001001100011001111011110
// 1001010010100101000010000
// 1111010000100001110011100
// 1001010000101101000010000
// 1001010010100101000010000
// 1001001100011101000011110
