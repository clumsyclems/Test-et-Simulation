#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdarg.h>  
/*
    Way to CUnit : -LC:/Users/rodri/Documents/3A/test_et_simulation/CUnit-2.1-3/CUnit/Sources/.libs
                    -IC:/Users/rodri/Documents/3A/test_et_simulation/CUnit-2.1-3/CUnit/Headers
                    -lcunit
*/

typedef struct information
{
    struct tm hour_alert; // when the alert is launched
    struct tm hour_expiration; // when the alert is expired
    double measure; // the measure done by the vehicule 
} information;

typedef struct message_alert
{
    double location [3] ; // vehicule's location when the alert is launched
    double dynamics [2] ; // vehicule's movement when the alert is launched
    information inf ; // information about the alert
} message_alert; 

typedef struct csc_return
{
    message_alert msg; //alert send by csc
    double output[2];
} csc_return;

extern message_alert message_builder(double radar , double braking_power);
extern message_alert communication_unit (message_alert msg);
extern csc_return chassis_safety_controller(int num, ...);
extern double *chassis_domain_bus (int num, ...);