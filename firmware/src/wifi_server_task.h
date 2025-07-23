#pragma once

#if SK_WIFI

#include <WiFi.h>

#include "task.h"
#include "serial/serial_protocol_protobuf.h"
#include "interface_task.h"

#ifndef WIFI_SSID
#define WIFI_SSID "YOUR_SSID"
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "YOUR_PASSWORD"
#endif

class WifiServerTask : public Task<WifiServerTask> {
    friend class Task<WifiServerTask>;

public:
    WifiServerTask(uint8_t task_core, InterfaceTask& interface_task);

protected:
    void run();

private:
    InterfaceTask& interface_task_;
    WiFiServer server_;
};

#endif // SK_WIFI
