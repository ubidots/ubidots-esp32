/*
Copyright (c) 2013-2020 Ubidots.
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

#include "UbiHttp.h"

#include "UbiUtils.h"

/**************************************************************************
 * Overloaded constructors
 ***************************************************************************/

UbiHTTP::UbiHTTP(const char *host, const int port, const char *user_agent, const char *token) {
  _host = host;
  _user_agent = user_agent;
  _token = token;
  _port = port;
  _client_https_ubi.setCACert(UBI_CA_CERT);
  _syncronizeTime();
}

/**************************************************************************
 * Destructor
 ***************************************************************************/

UbiHTTP::~UbiHTTP() {
  delete[] _host;
  delete[] _user_agent;
  delete[] _token;
}

bool UbiHTTP::sendData(const char *device_label, const char *device_name, char *payload) {
  bool allowed = _preConnectionChecks();
  if (!allowed) {
    return false;
  }

  /* Connecting the client */
  bool clientConnected = reconnect(_host, _port);
  if (!clientConnected) {
    return false;
  }

  int content_length = strlen(payload);
  if (_debug) {
    Serial.println("Making request to ubidots");
    Serial.print(F("POST /api/v1.6/devices/"));
    Serial.print(device_label);
    Serial.print(F(" HTTP/1.1"));
    Serial.print(F("\r\n"));
    Serial.print(F("Host: "));
    Serial.print(_host);
    Serial.print(F("\r\n"));
    Serial.print(F("User-Agent: "));
    Serial.print(_user_agent);
    Serial.print("\r\n");
    Serial.print(F("X-Auth-Token: "));
    Serial.print(_token);
    Serial.print("\r\n");
    Serial.print(F("Content-Type: application/json\r\n"));
    Serial.print(F("Content-Length: "));
    Serial.print(content_length);
    Serial.print(F("\r\n\r\n"));
    Serial.print(payload);
    Serial.print(F("\r\n"));
  }

  Serial.println("Connected to server!");
  _client_https_ubi.print(F("POST /api/v1.6/devices/"));
  _client_https_ubi.print(device_label);
  _client_https_ubi.print(F(" HTTP/1.1"));
  _client_https_ubi.print(F("\r\n"));
  _client_https_ubi.print(F("Host: "));
  _client_https_ubi.print(_host);
  _client_https_ubi.print(F("\r\n"));
  _client_https_ubi.print(F("User-Agent: "));
  _client_https_ubi.print(_user_agent);
  _client_https_ubi.print("\r\n");
  _client_https_ubi.print(F("X-Auth-Token: "));
  _client_https_ubi.print(_token);
  _client_https_ubi.print("\r\n");
  _client_https_ubi.print(F("Content-Type: application/json\r\n"));
  _client_https_ubi.print(F("Content-Length: "));
  _client_https_ubi.print(content_length);
  _client_https_ubi.print(F("\r\n\r\n"));
  _client_https_ubi.print(payload);
  _client_https_ubi.print(F("\r\n"));
  
  _client_https_ubi.flush();

  /* Reads the response from the server */
  if (waitServerAnswer()) {
    if (_debug) {
      Serial.println(F("\nUbidots' Server response:\n"));
      while (_client_https_ubi.available()) {
        char c = _client_https_ubi.read();
        Serial.print(c);
      }
    }

  } else {
    if (_debug) {
      Serial.println(F("Could not read server's response"));
    }
  }
  
  return true;
}

double UbiHTTP::get(const char *device_label, const char *variable_label) {
  bool allowed = _preConnectionChecks();
  if (!allowed) {
    return ERROR_VALUE;
  }

  /* Connecting the client */
  bool clientConnected = reconnect(_host, _port);
  if (!clientConnected) {
    return ERROR_VALUE;
  }

  uint16_t pathLength = _pathLength(device_label, variable_label);
  char *path = (char *)malloc(sizeof(char) * pathLength + 1);
  sprintf(path, "/api/v1.6/devices/%s/%s/lv", device_label, variable_label);

  if (_debug) {
    Serial.print(F("Requesting to URL: "));
    Serial.println(path);
  }

  uint16_t requestLineLength = _requestLineLength(path);
  char *message = (char *)malloc(sizeof(char) * requestLineLength + 1);
  sprintf(message,
          "GET %s HTTP/1.1\r\nHost: %s\r\nX-Auth-Token: "
          "%s\r\nUser-Agent: %s\r\nContent-Type: "
          "application/json\r\n\r\n",
          path, _host, _token, _user_agent);

  if (_debug) {
    Serial.println(F("Request sent"));
    Serial.println(message);
  }

  _client_https_ubi.print(message);
  _client_https_ubi.flush();
  
  free(message);
  free(path);
  
  double value = NAN;
  
  /* Reads the response from the server */
  if (waitServerAnswer()) {
    value = _parseServerAnswer();
  } else {
    if (_debug) {
      Serial.println(F("Could not read server's response"));
    }
  }
  
  return value;
}

double UbiHTTP::_parseServerAnswer() {
  String line;
  
  if (_debug) {
    Serial.println("Server response:");
  }
  /* Skip response headers */
  while (_client_https_ubi.connected()) {
    line = _client_https_ubi.readStringUntil('\n');
    if (_debug) {
      Serial.println(line);
    }
    if (line == "\r") {
      break;
    }
  }
  
  /* Parse value length */
  line = _client_https_ubi.readStringUntil('\n');
  unsigned long value_len = strtoul(line.c_str(), NULL, 16);
  
  /* Parse value */
  line = _client_https_ubi.readStringUntil('\n');
  double value = strtod(line.c_str(), NULL);
  
  if (_debug) {
    Serial.println(value_len);
    Serial.println(value);
  }
  
  /* Discard remaining data */
  while (_client_https_ubi.available()) {
    char c = _client_https_ubi.read();
    if (_debug) {
      Serial.write(c);
    }
  }

  return value;
}

/**
 * @brief Calculate the lenght of the request line to be send over HTTP to the
 * server
 *
 * @param path address of the endpoint to gather the data
 * @return uint16_t  Lenght of the request line
 */
uint16_t UbiHTTP::_requestLineLength(char *path) {
  uint16_t endpointLength = strlen(
                                "GET  HTTP/1.1\r\nHost: \r\nX-Auth-Token: "
                                "\r\nUser-Agent: \r\nContent-Type: "
                                "application/json\r\nConnection: close\r\n\r\n") +
                            strlen(path) + strlen(_host) + strlen(_token) + strlen(_user_agent);
  return endpointLength;
}

/**
 * @brief Calculate the lenght of the path to be send over HTTP to the server
 *
 * @param device_label device label of the device
 * @param variable_label variable label to be updated or fetched
 * @return uint16_t  Lenght of the endpoint path
 */
uint16_t UbiHTTP::_pathLength(const char *device_label, const char *variable_label) {
  uint16_t endpointLength = strlen("/api/v1.6/devices///lv") + strlen(device_label) + strlen(variable_label);
  return endpointLength;
}

/**
 * Reconnects to the server
 * @return true once the host answer buffer length is greater than zero,
 *         false if timeout is reached.
 */

bool UbiHTTP::reconnect(const char *host, const int port) {
  uint8_t attempts = 0;
  bool connected = _client_https_ubi.connected();
  while (!connected && attempts < _maxReconnectAttempts) {
    if (_debug) {
      Serial.print(F("Trying to connect to "));
      Serial.print(host);
      Serial.print(F(" , attempt number: "));
      Serial.println(attempts);
    }
    attempts += 1;
    connected = _client_https_ubi.connect(host, port);
    delay(1000);
  }
  if (connected) {
    if (_debug) {
      Serial.println(F("Connected"));
    }
  } else {
    if (_debug) {
      Serial.println(F("Could not connect to the server, please check your network and your firewall rules"));
    }
  }

  return connected;
}

/**
 * @arg response [Mandatory] Pointer to store the server's answer
 */

void UbiHTTP::_parsePartialServerAnswer(char *_serverResponse) {
  /**
   * Server Response Ascii code -> Character from the server
  First extract the following value
  52 -> 4     ->Length of the value in HEX
  13 -> \r
  10 -> \n

  At the next time it will read the whole value with the allocated memory set by the previus value extracted
  51 -> 3     ->Value in char
  57 -> 9     ->Value in char
  46 -> .     ->Decimal point
  48 -> 0     ->Value in char
  13 -> \r
  10 -> \n

  48 -> 0     ->Value in char
  13 -> \r
  10 -> \n

  13 -> \r
  10 -> \n
  */

  sprintf(_serverResponse, "%c", _client_https_ubi.read());

  while (_client_https_ubi.available()) {
    char charRead = (char)_client_https_ubi.read();
    char c[2];
    sprintf(c, "%c\0", charRead);
    if (charRead == '\r') {  // If the character is \r means we have ended the line then we request
      // Get the last character \n to enable the function to run again
      _client_https_ubi.read();  // clean the buffer asking for the next character
      break;
    } else if (charRead == 'e') {
      /**
       * After 18 digits it will show the response in scientific notation, and
       * there is no space to store such a  huge number
       * */
      sprintf(_serverResponse, "%f", ERROR_VALUE);
      if (_debug) {
        Serial.println(F("[ERROR]The value from the server exceeded memory capacity"));
      }
    } else {
      strcat(_serverResponse, c);  // Add the value to the expected response.
    }
  }
}

/**
 * Function to wait for the host answer up to the already set _timeout.
 * @return true once the host answer buffer length is greater than zero,
 *         false if timeout is reached.
 */

bool UbiHTTP::waitServerAnswer() {
  int timeout = 0;
  while (!_client_https_ubi.available() && timeout < _timeout) {
    timeout++;
    delay(1);
    if (timeout > _timeout - 1) {
      if (_debug) {
        Serial.println(F("timeout, could not read any response from the host"));
      }
      return false;
    }
  }
  return true;
}

/**
 * Makes available debug traces
 */

void UbiHTTP::setDebug(bool debug) { _debug = debug; }

/*
 * Checks if the socket is still opened with the Ubidots Server
 */

bool UbiHTTP::serverConnected() { return _client_https_ubi.connected(); }

/*
 * Syncronizes the internal timer to verify if the cert has expired
 */

bool UbiHTTP::_syncronizeTime() {
  // Synchronizes time using SNTP. This is necessary to verify that
  // the TLS certificates offered by the server are currently valid.
  if (_debug) {
    Serial.print(F("Setting time using SNTP"));
  }
  configTime(8 * 3600, 0, NTP_SERVER, NIST_SERVER);
  time_t now = time(nullptr);
  uint8_t attempts = 0;
  while (now < 8 * 3600 * 2 && attempts <= 5) {
    if (_debug) {
      Serial.print(".");
    }
    now = time(nullptr);
    attempts += 1;
    delay(500);
  }

  if (attempts > 5) {
    if (_debug) {
      Serial.println(F("[ERROR] Could not set time using remote SNTP to verify Cert"));
    }
    return false;
  }

  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  if (_debug) {
    Serial.print(F("Current time: "));
    Serial.print(asctime(&timeinfo));
  }
  return true;
}

bool UbiHTTP::_preConnectionChecks() {
  /* Synchronizes time every 60 minutes */
  bool syncronized = true;
  if (millis() - _timerToSync > 3600000) {
    syncronized = _syncronizeTime();
    _timerToSync = millis();
  }

  if (!syncronized) {
    if (_debug) {
      Serial.println(
          F("[ERROR] Could not syncronize device time with external "
            "source, make sure that you are not behind a "
            "firewall"));
    }
    return false;
  }

  return true;
}
