
/*
Copyright (c) 2013-2018 Ubidots.
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:
The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
Developed and maintained by Jose Garcia and Cristian Arrieta for IoT Services
Inc
@jotathebest at github: https://github.com/jotathebest
@crisap94 at github: https://github.com/crisap94
*/

#ifndef _Ubidots_H_
#define _Ubidots_H_

#include "UbiProtocolHandler.h"
#include "UbiConnectivityHandler.h"

class Ubidots {
public:
  explicit Ubidots(const char *token, connectivityType connectivity = UBI_WIFI, IotProtocol iotProtocol = UBI_TCP, UbiServer server = UBI_INDUSTRIAL);
  explicit Ubidots(const char *token, IotProtocol iotProtocol);
  explicit Ubidots(const char *token, UbiServer server = UBI_INDUSTRIAL, IotProtocol iotProtocol = UBI_TCP);
  void add(const char *variable_label, double value);
  void add(const char *variable_label, double value, char *context);
  void add(const char *variable_label, double value, char *context, unsigned long dot_timestamp_seconds);
  void add(const char *variable_label, double value, char *context, unsigned long dot_timestamp_seconds,
           unsigned int dot_timestamp_millis);
  void addContext(char *key_label, char *key_value);
  void getContext(char *context_result);
  void getContext(char *context_result, IotProtocol iotProtocol);
  bool send();
  bool send(const char *device_label);
  bool send(const char *device_label, const char *device_name);
  double get(const char *device_label, const char *variable_label);
  void setDebug(bool debug);
  
  bool wifiConnect(const char *ssid, const char *password);
  bool wifiConnected();
  bool serverConnected();
  void setDeviceType(const char *deviceType);

  bool connect(const char *ssid, const char *password);
  bool connect(const char *pin, const char *apn, const char *login, const char *password);
  bool isServerConnected();
  ~Ubidots();

private:
  char _deviceType[25];
  uint8_t _maxConnectionAttempts = 20;
  UbiProtocolHandler *_cloudProtocol;
  UbiConnectivityHandler * _connectivityProtocol;
  char _defaultDeviceLabel[18];
  ContextUbi *_context;
  IotProtocol _iotProtocol;
  int8_t _current_context = 0;
  bool _debug = false;
  void _builder(const char *token, UbiServer server, IotProtocol iot_protocol, connectivityType connectivity = UBI_WIFI);
  void _getDeviceMac(char macAddr[]);
};

#endif
