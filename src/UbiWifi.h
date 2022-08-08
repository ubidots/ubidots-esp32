#ifndef _UBI_WIFI_
#define _UBI_WIFI_

#include "UbiConnectivity.h"


class UbiWifi : public UbiConnectivity
{
    public:
        virtual bool connect() ;
        virtual bool isConnected();
        virtual bool isServerConnected();
        virtual void getDeviceMAC(char mac[]);
};

#endif