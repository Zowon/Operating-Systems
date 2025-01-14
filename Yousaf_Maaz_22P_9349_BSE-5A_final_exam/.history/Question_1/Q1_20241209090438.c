#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
sem_t semaphore;

void *Device_Application()
{
    int light;
    int thermostats;
    int security_system;
    int appliances;
    
    printf("light starting ... Intialization" , light );
    sem_wait(&semaphore);

    printf("Thermostats ....  Intialization" , thermostats );
    sem_wait(&semaphore);

    printf("Security cameras .. intialization", security_system );
    sem_wait(&semaphore);

    printf("security")




}

int main()
{

    return 0;
}