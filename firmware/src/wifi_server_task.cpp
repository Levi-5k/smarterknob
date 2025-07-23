#if SK_WIFI

#include "wifi_server_task.h"

WifiServerTask::WifiServerTask(uint8_t task_core, InterfaceTask& interface_task)
    : Task("WiFi", 4096, 1, task_core),
      interface_task_(interface_task),
      server_(6969) {}

void WifiServerTask::run() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    server_.begin();

    while (1) {
        WiFiClient client = server_.available();
        if (client) {
            SerialProtocolProtobuf proto(client, [this](PB_SmartKnobConfig& cfg) {
                interface_task_.applyRemoteConfig(cfg);
            });
            while (client.connected()) {
                proto.loop();
                delay(1);
            }
        }
        delay(10);
    }
}

#endif // SK_WIFI
