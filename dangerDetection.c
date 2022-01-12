#include "dangerDetection.h"

double vehicule_speed = 50 ; // vehicule speed in km/h
double actual_location [3] = {45.8715, -52.5428, 66.6441 } ; //current location of the vehicule
double dist_to_brake = 25 ;// distance when the vehicle must start to brake

message_alert message_builder(double radar , double braking_power)
{
    time_t t = time(NULL);
    message_alert msg;
    double tmp[2] = {0, vehicule_speed};
    memcpy(msg.location ,actual_location, sizeof(msg.location));
    memcpy(msg.dynamics ,tmp, sizeof(msg.dynamics));
    msg.inf.measure = braking_power;
    msg.inf.hour_alert = *localtime(&t);
    msg.inf.hour_expiration = *localtime(&t);
    msg.inf.hour_expiration.tm_sec += vehicule_speed / (3.6 * braking_power);

    return msg;

}

message_alert communication_unit (message_alert msg)
{
    time_t t = time(NULL);
    struct tm current_time = *localtime(&t);
    if (difftime(mktime(&current_time), mktime(&msg.inf.hour_expiration)) < 0)
    {
        return msg;
    }
    else
    {
        return message_builder(dist_to_brake + 10, 0);
    }
}

csc_return chassis_safety_controller(int num, ...)
{
    double radar;
    double braking_power;
    csc_return csc;

    if (num == 2)
    {
        va_list valist;
        va_start(valist, num);
        radar = va_arg(valist, double);
        va_end(valist);

        if (radar <= dist_to_brake)
        {
            braking_power = (vehicule_speed * vehicule_speed) / 2 * radar;
            csc.msg = message_builder(radar, braking_power);
            csc.output[0] = radar;
            csc.output[1] = braking_power;
        }
    }
    else if (num == 1)
    {
        va_list valist;
        va_start(valist, num);
        csc.msg = va_arg(valist, message_alert);
        va_end(valist);

        if (csc.msg.location[2] - actual_location[2] <= 10 
         && csc.msg.location[0] + csc.msg.location[1] - actual_location[0] - actual_location[1] <= 20)
         {
             csc.output[0] = csc.msg.location[0] + csc.msg.location[1] - actual_location[0] - actual_location[1];
             csc.output[1] = (vehicule_speed * vehicule_speed) / 2 * csc.output[0];
         }
    }
    else
    {
                printf("\n\t*********Invalid Value********* \n");
    }

    return csc;

}

double *chassis_domain_bus (int num, ...)
{
    static double output [2];

    if (num == 2)
    {
        va_list valist;
        va_start(valist, num);
        output[0] = (double) va_arg(valist, double);
        output[1] = (double) va_arg(valist, double);
        va_end(valist);
    }
    else if (num == 1)
    {
        va_list valist;
        va_start(valist, num);
        output[0] = va_arg(valist, double);
        
        va_end(valist);
    }
    else
    {
        printf("\n\t*********Invalid Value********* \n");
    }
    return output;
}
/*
int main(int argc, char *argv[])
{   
    return EXIT_SUCCESS;
}
*/
