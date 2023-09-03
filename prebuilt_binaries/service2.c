#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <math.h>
#include <float.h>
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

    // Variables for statistics
    float sum_temperature = 0.0;
    float sum_humidity = 0.0;
    float sum_lightIntensity = 0.0;
    float min_temperature = FLT_MAX;
    float min_humidity = FLT_MAX;
    float min_lightIntensity = FLT_MAX;
    float max_temperature = FLT_MIN;
    float max_humidity = FLT_MIN;
    float max_lightIntensity = FLT_MIN;
    int count = 0;

    while (1) {
        struct Message message;
        if (msgrcv(msgQueueID, &message, sizeof(struct SensorData), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        // Process received data here
        sum_temperature += message.data.temperature;
        sum_humidity += message.data.humidity;
        sum_lightIntensity += message.data.lightIntensity;

        if (message.data.temperature < min_temperature) {
            min_temperature = message.data.temperature;
        }

        if (message.data.humidity < min_humidity) {
            min_humidity = message.data.humidity;
        }

        if (message.data.lightIntensity < min_lightIntensity) {
            min_lightIntensity = message.data.lightIntensity;
        }

        if (message.data.temperature > max_temperature) {
            max_temperature = message.data.temperature;
        }

        if (message.data.humidity > max_humidity) {
            max_humidity = message.data.humidity;
        }

        if (message.data.lightIntensity > max_lightIntensity) {
            max_lightIntensity = message.data.lightIntensity;
        }

        count++;

        custom_log("#########################################################\n");
        custom_log("#############           STATS           #################\n");
        custom_log("#########################################################\n");
        custom_log("Number of measurements: %d\n", count);
        custom_log("#############           Averages        #################\n");
        custom_log("Average temperature: %.2f\n", sum_temperature / count);
        custom_log("Average humidity: %.2f\n", sum_humidity / count);
        custom_log("Average light intensity: %.2f\n", sum_lightIntensity / count);
        custom_log("#############           Min/max         #################\n");
        custom_log("Minimum temperature: %.2f\n", min_temperature);
        custom_log("Maximum temperature: %.2f\n", max_temperature);
        custom_log("Minimum humidity: %.2f\n", min_humidity);
        custom_log("Maximum humidity: %.2f\n", max_humidity);
        custom_log("Minimum light intensity: %.2f\n", min_lightIntensity);
        custom_log("Maximum light intensity: %.2f\n", max_lightIntensity);
    }

    return 0;
}
