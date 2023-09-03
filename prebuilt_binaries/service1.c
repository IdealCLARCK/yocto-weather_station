#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

// Constants for file permissions
#define MESSAGE_QUEUE_PERMISSIONS 0666

// Structure for storing sensor data
struct SensorData {
    float temperature;
    float humidity;
    float lightIntensity;
};

// Structure for messages
struct Message {
    long messageType;
    struct SensorData data;
};

int msgQueueID;

// Function for cleaning up and terminating the service
void cleanup(int signum) {
    // Cleanly close the message queue here
    msgctl(msgQueueID, IPC_RMID, NULL);
    exit(0);
}

int main() {
    key_t msgQueueKey;

    // Create a unique key for the message queue
    msgQueueKey = ftok("/tmp", 'A');
    if (msgQueueKey == -1) {
        perror("ftok");
        exit(1);
    }

    // Create a message queue (with improved error handling)
    msgQueueID = msgget(msgQueueKey, MESSAGE_QUEUE_PERMISSIONS | IPC_CREAT);
    if (msgQueueID == -1) {
        perror("msgget");
        exit(1);
    }

    // Initialize the random number generator with a seed based on the current time
    srand(time(NULL));

    // Configuration of signal handling for clean exit
    signal(SIGTERM, cleanup);

    while (1) {
        // Generate simulated sensor data
        struct SensorData sensorData;
        sensorData.temperature = (float)(rand() % 30) + ((float)rand() / RAND_MAX); // Temperature between 0 and 30°C
        sensorData.humidity = (float)(rand() % 100) + ((float)rand() / RAND_MAX);    // Humidity between 0% and 100%
        sensorData.lightIntensity = (float)(rand() % 1000) + ((float)rand() / RAND_MAX); // Light intensity between 0 and 1000 Lux

        // Create a message with sensor data and send it to the message queue
        struct Message message;
        message.messageType = 1; // Arbitrary message type
        message.data = sensorData;

        if (msgsnd(msgQueueID, &message, sizeof(struct SensorData), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        // Wait for a certain time interval (e.g., 1 second)
        sleep(1);
    }

    return 0;
}
