#include<istream.h>
#include<iostream>
#include<sys/types.h>
#include<unistd.h>

int main() {
    cout << "PID of the current process: " << getpid() << endl;
    return 0;
}
