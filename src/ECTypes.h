#ifndef ECTYPES_H
#define ECTYPES_H

#include <IPAddress.h>

template<typename Tret, typename T>
Tret lambda_ptr_exec(T* v) {
    return (Tret) (*v)();
}

template<typename Tret = void, typename Tfp = Tret(*)(), typename T>
Tfp lambda_ptr(T& v) {
    return (Tfp) lambda_ptr_exec<Tret, T>;
}

typedef struct
{
    char ssid[32];
    char pass[63];
    char name[50];
    char mqttClientid[32];
    char mqttUsername[32];
    char mqttPass[32];
    char mqttTopic[32];
    char mqttFulltopic[100];
    char mqttHost[16];
    char mqttPort[6];
} ECSettings;

#endif