#ifndef UBI_CONNECTIVITY_HANDLER
#define UBI_CONNECTIVITY_HANDLER

#include "UbiConnectivityBuilder.h"

class UbiConnectivityHandler
{
    public:
        explicit UbiConnectivityHandler(connectivityType connectivity);
        bool connect();
    private:
        connectivityCredentials _credentials;
        connectivityType _connectivity;
        UbiConnectivity *_connectivityProtocol;
};




#endif