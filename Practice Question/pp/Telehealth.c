#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *device_monitor(void *arg)
{
    const char *device_name = (const char *)arg;
    printf("%s initialized.\n", device_name);
    while (1)
    {
        printf("%s is updating...\n", device_name);
        sleep(1); // Simulate periodic update
    }
}

int main()
{
    pthread_t threads[5];
    const char *devices[] = {"Heart Rate Monitor", "Oxygen Monitor", "Blood Pressure Monitor", "Glucose Monitor", "Respiratory Monitor"};
    int intervals[] = {4, 3, 10, 3, 5};

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&threads[i], NULL, device_monitor, (void *)devices[i]);
        sleep(intervals[i]); // Sleep according to the device's update interval
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}