#include <unistd.h>
#include <stdio.h>

int main() {
    printf("Using execl to run /bin/ls\n");
    execl("/bin/ls", "ls", "-l", NULL);
    perror("execl failed");
    return 1;
}


#include <unistd.h>
#include <stdio.h>

int main() {
    printf("Using execlp to run ls\n");
    execlp("ls", "ls", "-l", NULL);
    perror("execlp failed");
    return 1;
}

#include <unistd.h>
#include <stdio.h>

int main() {
    char *env[] = {"HOME=/custom_home", "PATH=/usr/bin", NULL};
    printf("Using execle to run /bin/ls\n");
    execle("/bin/ls", "ls", "-l", NULL, env);
    perror("execle failed");
    return 1;
}

#include <unistd.h>
#include <stdio.h>

int main() {
    char *args[] = {"ls", "-l", NULL};
    printf("Using execv to run /bin/ls\n");
    execv("/bin/ls", args);
    perror("execv failed");
    return 1;
}

#include <unistd.h>
#include <stdio.h>

int main() {
    char *args[] = {"ls", "-l", NULL};
    char *env[] = {"HOME=/custom_home", "PATH=/usr/bin", NULL};
    printf("Using execve to run /bin/ls\n");
    execve("/bin/ls", args, env);
    perror("execve failed");
    return 1;
}

#include <unistd.h>
#include <stdio.h>

int main() {
    char *args[] = {"ls", "-l", NULL};
    printf("Using execvp to run ls\n");
    execvp("ls", args);
    perror("execvp failed");
    return 1;
}
