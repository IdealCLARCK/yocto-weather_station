#include "custom_logger.h"
#include <stdio.h>
#include <syslog.h>
#include <stdarg.h> 

void custom_log(const char* format, ...)  {
    // Condition to choose between printf and syslog based on the ARM_BUILD macro
    #ifdef ARM_BUILD
        openlog("ServiceLog", LOG_PID | LOG_CONS, LOG_USER);
        va_list args;
        va_start(args, format);
        vsyslog(LOG_INFO, format, args);
        va_end(args);
        closelog();
    #else
        va_list args;  // Declare a variable arguments list
        va_start(args, format);  // Initialize the variable arguments list
        vprintf(format, args);  // Use vprintf to handle variable arguments
        va_end(args);  // Finish handling variable arguments
    #endif
}
