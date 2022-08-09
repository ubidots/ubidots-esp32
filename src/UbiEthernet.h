#ifndef _UBI_ETHERNET
#define _UBI_ETHERNET

#include "UbiConnectivity.h"


class UbiEthernet : public UbiConnectivity
{
    public:
        UbiEthernet(connectivityCredentials credentials);
        ~UbiEthernet();
        bool connect() ;
        bool isConnected();
        bool isServerConnected();
        void getDeviceMAC(char mac[]);
        connectivityCredentials credentials;
    private:
};

#endif