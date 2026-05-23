#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

 int temperature = 200;
 int pressure = 30;
 
 int running = 1;

 pthread_mutex_t lock;

 void* monitor_temp(void* arg)
{
 while(running)
{
 pthread_mutex_lock(&lock);

 temperature += (rand() % 11) - 5;
 
 if(temperature < 180)
    temperature = 180;

 if(temperature > 260)
    temperature = 260;

 pthread_mutex_unlock(&lock);

 sleep(1);

}

 return NULL;

}

 void* monitor_pressure(void* arg)

{

 while(running)

{

 pthread_mutex_lock(&lock);

 pressure += (rand() % 5) -2;
 
 if(pressure < 25)
    pressure = 25;

 if(pressure > 45)
    pressure = 45;

 pthread_mutex_unlock(&lock);

 sleep(1);

}

 return NULL;

}
 
 int main() 

{

 pthread_t temp_thread, pressure_thread;

 FILE *logfile;

 srand(time(NULL));

 pthread_mutex_init(&lock, NULL);

 printf("\033[1;34m");

 printf("=============================================\n");

 printf("  SMART POWER PLANT BOILER MONITOR\n");
 
 printf("=============================================\n");
 
 printf("\033[0m");

 sleep(2);

 pthread_create(&temp_thread, NULL, monitor_temp, NULL);
 pthread_create(&pressure_thread, NULL, monitor_pressure, NULL);
 
 while(running)

{

 system("clear");
 
 pthread_mutex_lock(&lock);

 printf("\033[1;36m");

 printf("============================================\n");

 printf("       LIVE BOILER STATUS DASHBOARD\n");

 printf("============================================\n");

 printf("\033[0m");

 printf("\033[1;33m");

 printf("Boiler Temperature : %d\u00B0C\n", temperature);

 printf("Steam Pressure    : %d PSI\n", pressure);

 printf("\033[0m");

 if(temperature < 220 && pressure < 35)

{
 
 printf("\n");

 printf("\033[1;32m");
 
 printf("System Status : NORMAL\n");

 printf("\033[0m");

 }

 else if((temperature >= 220 && temperature < 230) || (pressure >= 35 && pressure < 36))

{
 
 printf("\n");

 printf("\033[1;33m");
 
 printf("WARNING : PARAMETERS RISING\n");

 printf("CHECK BOILER CONDITIONS\n");

 printf("\033[0m");

 }

 else if (temperature >= 230 || pressure >= 36) 

{

 printf("\n");

 printf("\033[1;31m");

 printf("!!! CRITICAL WARNING !!!\n");

 printf("LIMITS EXCEEDED - EMERGENCY SHUTDOWN\n");

 printf("\033[0m");

 logfile = fopen("alerts.txt","a");

 if(logfile == NULL)

{

 printf("ERROR OPENING LOG FILE!\n");

}

 else

{

 time_t now;
 time(&now);

 char *time_string = ctime(&now);

 time_string[strlen(time_string) - 1] = '\0';

 fprintf(logfile," [%s] ALERT -> Temperature: %d\u00B0C | Pressure: %d PSI\n",time_string,temperature,pressure);

 fclose(logfile);

 printf("\nAlert logged successfully!\n");

}

 running = 0;

}

 pthread_mutex_unlock(&lock);

 sleep(1);

}
 
 pthread_join(temp_thread, NULL);
 pthread_join(pressure_thread, NULL);
 
 pthread_mutex_destroy(&lock);

 printf("\n");
 
 printf("\033[1:32m");

 printf("System safely depressurized.\n");
 
 printf("\033[0m");

 return 0;

}
