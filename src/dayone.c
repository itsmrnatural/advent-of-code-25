#include <stdio.h>
#include <stdlib.h>

int rotation(char direction, int distance) {
    if (direction == 'L') {
        return -(distance);
    } else {
        return distance;
    }
}

void dial(int distance, int *code) {
    static int position = 50;  // At the beginning the dial is at 50
    int hasPassed = 0;

    (*code) += (abs(distance) / 100);
    distance %= 100;  // Just turn effectively

    if (position == 0) {
        hasPassed = 1;
    }
    position += distance;  // Turn the dial

    if (position < 0) {
        position += 100;  // For wrapping logic
        if (hasPassed != 1) (*code)++;
        hasPassed = 1;
    } else if (position >= 100) {
        position -= 100;  // For wrapping logic
        if (hasPassed != 1) (*code)++;
        hasPassed = 1;
    }

    if (position == 0 && hasPassed != 1) {
        (*code)++;
    }

    printf("Dial: %3d | ", position);
    printf("Rotated by: %d\n", distance);
}

void begin(void) {
    int code = 0;  // Number of times dial stopped at 0

    FILE *fp = fopen("dayone_input.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    // fsetpos(fp, 0); // Set position to the beginning of the file

    while (!feof(fp)) {
        char direction;
        int distance = 0;
        fscanf(fp, "%c%d\n", &direction, &distance);

        int rotate = rotation(direction, distance);
        dial(rotate, &code);
    }

    printf("Passcode: %d\n", code);
}

int main(void) {
    printf("Beginning the code breaking.\n");
    begin();
    printf("Finished!\n");
    return 0;
}
