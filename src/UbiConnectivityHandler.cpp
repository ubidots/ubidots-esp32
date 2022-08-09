#include "UbiConnectivityHandler.h"



UbiConnectivityHandler::UbiConnectivityHandler(connectivityType connectivity)
{
    _builder(connectivity);
}


void UbiConnectivityHandler::_builder(connectivityType connectivity)
{
    _connectivity = connectivity;
    UbiConnectivityBuilder builder(connectivity);
    _connectivityProtocol = builder.builder();

}



bool UbiConnectivityHandler::connect(const char *ssid, const char *password)
{
    if( _connectivity == UBI_WIFI)
    {
        connectivityCredentials wifiCredentials {{_SSID_,ssid},{_PASSWORD_, password}};
        _connectivityProtocol->credentials = wifiCredentials;
        return _connectivityProtocol->connect();
    }
    else 
    {
        Serial.println("[You are using the wrong connect method]");
        return false;
    }

}
bool UbiConnectivityHandler::connect(const char *pin, const char *apn, const char *login, const char *password)
{

}
bool UbiConnectivityHandler::isConnected()
{

}
bool UbiConnectivityHandler::isServerConnected()
{

}
void UbiConnectivityHandler::getDeviceMac(char mac[])
{

}



