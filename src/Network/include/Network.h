/*
 * Network.h
 *
 *  Created on: Dec 17, 2017
 *      Author: Daniel Yuan
 */

#ifndef SRC_NETWORK_H_
#define SRC_NETWORK_H_

#include "TcpServerSocket.h"
#include "NetworkConfig.h"
#include "UdpSocket.h"
#include "ScanDriver.h"
#include "Ipc.h"

#include <mutex>
#include <condition_variable>
#include <thread>

//class TcpSocket;
extern volatile int tcpUdpPortVal;

class Network
{
public:
    Network(int port = 0);
    virtual ~Network();
    int GetServerPort() const;
    void SetServerPort(int);
    void Start();
    void Stop();

    int RegisterScanDriver(ScanDriver *scan_driver, EventManager *event_manager);
    int UnRegisterScanDriver();
    int RegisterConfiguration(READER_CONFIGURATION *pRConfg);
    int UnRegisterConfiguration();
	

	int StarThread();
    int StopThread();
	
private:
	void NetworkListenerThread();
    //bool isContinusWattingForConnection = false;
    TcpServerSocket *pTcpSocket = NULL;
	
	TcpServerSocket *pTcpSocketConfig = NULL; //For recving and sending configuration data 
    TcpServerSocket *pTcpSocketImage = NULL;  //For sending image data to PC host
    TcpServerSocket *pTcpDecoderData = NULL;  //For sending decoder data and Image index to PC host
    
    UdpSocket *pUdpSocket = NULL;
	NetworkConfig *pNwCong = NULL;
	
    int  TcpServerPort = -1;
	int  UdpPort = -1;
    bool isThreadRunning = false;
    std::thread listenerT;
	std::mutex mtx;
	std::condition_variable cv;

protected:

};

int InitNetworkServer(int tcpPort,int udpPort,ScanDriver *scan_driver, EventManager *event_manager,READER_CONFIGURATION *pRConfg);
int StartNetworkServer();
int StopNetworkServer();

#endif /* SRC_NETWORK_H_ */



