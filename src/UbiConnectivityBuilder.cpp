#include "UbiConnectivityBuilder.h"


UbiConnectivityBuilder::UbiConnectivityBuilder(connectivityType connectivity , connectivityCredentials credentials)
{
    connectivityCredentials wifiConnectivityCredentials { {"ssid", ""}, {"password", ""}};
    connectivityCredentials ethernetConnectivityCredentials { {"pin-number", ""}, {"apn", ""}, {"user-login", ""}, {"password", ""}};
    connectivityCredentials mobileConnectivityCredentials { {"ssid", ""}, {"password", ""}};
}


UbiConnectivity *UbiConnectivityBuilder::builder()
{



}