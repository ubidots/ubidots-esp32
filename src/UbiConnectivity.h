#ifndef UBI_CONNECTIVITY_H
#define UBI_CONNECTIVITY_H

class UbiConnectivity
{

    public:

        virtual bool connect() = 0;
        virtual bool isConnected() = 0;
        virtual bool isServerConnected() = 0;
        virtual void getDeviceMAC(char mac[]);
}



#endif