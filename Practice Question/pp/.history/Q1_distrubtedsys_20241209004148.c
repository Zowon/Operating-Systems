#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void pv1(int pipe1[]) {
    close(pipe1[0]); // Close read end
    const char *filenames[] = {"video1.mp4", "video2.mp4", NULL};
    for (int i = 0; filenames[i] != NULL; i++) {
        write(pipe1[1], filenames[i], strlen(filenames[i]) + 1);
    }
    close(pipe1[1]); // Close write end
}

void pv2(int pipe1[], int pipe2[]) {
    close(pipe1[1]); // Close write end
    close(pipe2[0]); // Close read end
    char filename[100];
    while (read(pipe1[0], filename, sizeof(filename))) {
        strcat(filename, "_transcoded");
        write(pipe2[1], filename, strlen(filename) + 1);
    }
    close(pipe1[0]);
    close(pipe2[1]);
}

void pv3(int pipe2[], int pipe3[]) {
    close(pipe2[1]); // Close write end
    close(pipe3[0]); // Close read end
    char filename[100];
    while (read(pipe2[0], filename, sizeof(filename))) {
        strcat(filename, "_QC_Passed");
        write(pipe3[1], filename, strlen(filename) + 1);
    }
    close(pipe2[0]);
    close(pipe3[1]);
}

void pv4(int pipe3[]) {
    close(pipe3[1]); // Close write end
    char filename[100];
    while (read(pipe3[0], filename, sizeof(filename))) {
        printf("Distributing: %s\n", filename);
    }
    close(pipe3[0]);
}

int main() {
    int pipe1[2], pipe2[2], pipe3[2];
    pipe(pipe1);
    pipe(pipe2);
    pipe(pipe3);

    if (fork() == 0) pv1(pipe1);
    if (fork() == 0) pv2(pipe1, pipe2);
    if (fork() == 0) pv3(pipe2, pipe3);
    if (fork() == 0) pv4(pipe3);

    return 0;
}