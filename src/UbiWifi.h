#ifndef _UBI_WIFI_
#define _UBI_WIFI_

#include "UbiConnectivity.h"


class UbiWifi : public UbiConnectivity
{
    public:
        bool connect() ;
        bool isConnected();
        bool isServerConnected();
        void getDeviceMAC(char mac[]);
    private:
        connectivityCredentials credentials;
};

#endif