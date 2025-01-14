#include<istream.h>
#include<iostream>
#include<sys/types.h>
#include<unistd.h>
using namespace std;

int main() {
    cout << "PID of the current process: " << getpid() << endl;
    cout<<"ppid of the parent process:"<<
    return 0;
}
