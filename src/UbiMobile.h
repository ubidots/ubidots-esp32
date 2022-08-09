#ifndef _UBI_MOBILE
#define _UBI_MOBILE

#include "UbiConnectivity.h"


class UbiMobile : public UbiConnectivity
{
    public:
        UbiMobile(connectivityCredentials credentials);
        ~UbiMobile();
        bool connect() ;
        bool isConnected();
        bool isServerConnected();
        void getDeviceMAC(char mac[]);
        connectivityCredentials credentials;
    private:
};

#endif