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
    
    printf("light starting ... Intializationling" , light );
    sem_wait(&semaphore);

    printf("Thermostats ....  Intializationling" , thermostats );
    sem_wait(&semaphore);

    printf("Security cameras .. intiali")




}

int main()
{

    return 0;
}