#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
void create_process_tree() {
    pid_t p1 = fork();
    if (p1 == 0) {
        // Child P1
        pid_t p2 = fork();
        if (p2 == 0) {
            // Child P2
            fork(); // Create P3
            fork(); // Create P4
        }
        pid_t p5 = fork();
        if (p5 == 0) {
            // Child P5
            fork(); // Create P6
            fork(); // Create P7
        }
    } else {
        // Parent P1
        fork(); // Create P8
    }
}

int main() {
    create_process_tree();
    return 0;
}