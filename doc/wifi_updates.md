# WiFi based configuration updates

This document outlines the initial plan for supporting live menu and configuration updates over WiFi.

The ESP32 firmware now includes a simple WiFi server (disabled by default). When enabled the device joins the configured network and listens for TCP connections on port `6969`.  Each connected client speaks the same protobuf based protocol that is currently used over the serial connection.

A new task `WifiServerTask` is responsible for maintaining the server and relaying any received `SmartKnobConfig` messages to `InterfaceTask`.  Because the protobuf protocol was already designed to be transport agnostic no changes were required to the message format.

To enable WiFi support define the following build flags in `platformio.ini`:

```ini
-DWIFI_SSID="your-ssid"
-DWIFI_PASSWORD="your-password"
-DSK_WIFI=1
```

See `firmware/src/wifi_server_task.h` for the compile time options.  The existing Python example can be adapted to open a TCP socket instead of a serial port in order to update the menu configuration in real time.
