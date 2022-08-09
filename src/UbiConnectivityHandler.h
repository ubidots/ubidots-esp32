#ifndef UBI_CONNECTIVITY_HANDLER
#define UBI_CONNECTIVITY_HANDLER

#include "UbiConnectivityBuilder.h"

class UbiConnectivityHandler
{
    public:
        explicit UbiConnectivityHandler(connectivityType connectivity);
        bool connect(const char *ssid, const char *password);
        bool connect(const char *pin, const char *apn, const char *login, const char *password);
        bool isConnected();
        bool isServerConnected();
        void getDeviceMac(char mac[]);
    private:
        UbiConnectivity *_connectivityProtocol;
        void _builder(connectivityType connectivity);
        connectivityType _connectivity;
};




#endif