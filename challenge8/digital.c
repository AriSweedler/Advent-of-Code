#include "digital.h"

int main(int argc, char** argv) {
    char file[15002];
    read(STDIN_FILENO, file, 15001);
    file[15001] = '\0';
    int min0s = sizeof(Layer) + 1;
    int answer = 0;
    for (int layer = 0; layer < 100; layer++) {
        int counter[3] = {0, 0, 0};
        for (int i = 0; i < sizeof(Layer); i++) {
            char c = file[layer*sizeof(Layer) + i];
            int char_code = c - '0';
            counter[char_code]++;
        }
        if (counter[0] < min0s) {
            printf("Layer %d has %d zeros\n", layer, counter[0]);
            min0s = counter[0];
            answer = counter[1] * counter[2];
            printf("\tAnswer for this layer is %d\n", answer);
        }
    }

    printf("Answer is: %d\n", answer);
    return 0;
}

// the Elves would like you to find the layer that contains the fewest 0 digits.
// On that layer, what is the number of 1 digits multiplied by the number of 2
// digits?
