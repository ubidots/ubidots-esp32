#include "UbiConnectivityBuilder.h"
#include "UbiWifi.h"
#include "UbiEthernet.h"
#include "UbiMobile.h"


UbiConnectivityBuilder::UbiConnectivityBuilder(connectivityType connectivity)
{ 
    __connectivity = connectivity;
    _classInstances[UBI_WIFI] = &wifiInstance;
    _classInstances[UBI_MOBILE] = &mobileInstance;
    _classInstances[UBI_ETHERNET] = &ethernetInstance;
    

}


UbiConnectivity *UbiConnectivityBuilder::builder()
{
    classInstances::iterator i = _classInstances.find(__connectivity);
    UbiConnectivity *UbiBuilder = (i->second)();
    return UbiBuilder;
}

UbiConnectivity *wifiInstance()
{
   UbiConnectivity *instance = new UbiWifi(__credentials);
   return instance;
}

UbiConnectivity *mobileInstance()
{
   UbiConnectivity *instance = new UbiMobile(__credentials);
   return instance;
}

UbiConnectivity *ethernetInstance()
{
   UbiConnectivity *instance = new UbiEthernet(__credentials);
   return instance;
}
