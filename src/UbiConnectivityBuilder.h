#ifndef UBI_CONNECTIVITY_BUILDER
#define UBI_CONNECTIVITY_BUILDER

#include <map>
#include <iostream>
#include "UbiConnectivity.h"
#include <functional>

UbiConnectivity *wifiInstance();
UbiConnectivity *mobileInstance();
UbiConnectivity *ethernetInstance();

typedef std::function<UbiConnectivity* ()> classFun;
typedef std::map<connectivityType, classFun> classInstances;


namespace
{
    connectivityCredentials __credentials;
    connectivityType __connectivity;
}

class UbiConnectivityBuilder
{
    public:
        explicit UbiConnectivityBuilder(connectivityType connectivity);
        UbiConnectivity *builder();
    private:
        classInstances _classInstances;
};




#endif