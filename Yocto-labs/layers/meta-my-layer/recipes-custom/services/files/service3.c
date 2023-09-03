#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "custom_logger.h"

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

int main() {
    key_t msgQueueKey;
    int msgQueueID;

    // Create a unique key for the message queue
    msgQueueKey = ftok("/tmp", 'A');
    if (msgQueueKey == -1) {
        perror("ftok");
        exit(1);
    }

    // Create a message queue
    msgQueueID = msgget(msgQueueKey, 0666 | IPC_CREAT);
    if (msgQueueID == -1) {
        perror("msgget");
        exit(1);
    }

    // Loop to monitor and generate alerts
    struct Message message;
    while (1) {
        if (msgrcv(msgQueueID, &message, sizeof(struct SensorData), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        // Monitor received data here for abnormal values
        if (message.data.temperature > 27.0) {
            // Generate an alert for high temperature
            custom_log("Alert: Critical temperature detected (%.2f °C)\n", message.data.temperature);
        }
        else if (message.data.temperature < 5.0) {
            // Generate an alert for low temperature
            custom_log("Alert: Critical temperature detected (%.2f °C)\n", message.data.temperature);
        }

        if (message.data.humidity > 90.0) {
            // Generate an alert for high humidity
            custom_log("Alert: Critical humidity detected (%.2f %%)\n", message.data.humidity);
        }
        else if (message.data.humidity < 10.0) {
            // Generate an alert for low humidity
            custom_log("Alert: Critical humidity detected (%.2f %%)\n", message.data.humidity);
        }

        if (message.data.lightIntensity > 900.0) {
            // Generate an alert for high light intensity
            custom_log("Alert: Critical light intensity detected (%.2f Lux)\n", message.data.lightIntensity);
        }
        else if (message.data.lightIntensity < 50.0) {
            // Generate an alert for low light intensity
            custom_log("Alert: Critical light intensity detected (%.2f Lux)\n", message.data.lightIntensity);
        }
    }

    return 0;
}
