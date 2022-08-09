#ifndef UBI_CONNECTIVITY_BUILDER
#define UBI_CONNECTIVITY_BUILDER

#include <map>
#include <iostream>
#include "UbiConnectivity.h"

UbiConnectivity *wifiInstance();
UbiConnectivity *mobileInstance();
UbiConnectivity *ethernetInstance();



class UbiConnectivityBuilder
{
    private:

    public:
        explicit UbiConnectivityBuilder(connectivityType connectivity ,connectivityCredentials credentials);
        UbiConnectivity *builder();
        ~UbiConnectivityBuilder();
};




#endif