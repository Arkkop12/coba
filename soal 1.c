#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> // Untuk EXIT_FAILURE

#include <sys/wait.h>

void abjad_shift_1() {
    int i;
    for (i = 65; i < 78; i++) {
        printf("%c\n", i);
    }
}

void abjad_shift_2() {
    int i;
    for (i = 78; i < 91; i++) { // Ubah variabel dari '1' menjadi 'i' dan batas perulangan
        printf("%c\n", i);
    }
}

int main() {
    pid_t child_id;

    child_id = fork(); // Ganti 'child_id fork();' menjadi 'child_id = fork();'

    if (child_id < 0) {
        exit(EXIT_FAILURE);
    }

    if (child_id == 0) {
        abjad_shift_1();
        exit(0);
    } else {
        wait(NULL);
        abjad_shift_2();
    }
    return 0;
}
