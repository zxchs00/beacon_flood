#include <iostream>
#include <unistd.h>

#include <tins/tins.h>

using namespace Tins;
using namespace std;

int main(int argc, char *argv[])
{
    char mac[18] = "00:07:89:00:00:00";
    char ssid[20] = "길길짱잘생김0";

    RadioTap radio;
    PacketSender sender;
    NetworkInterface iface("wlan0");

    while(true){
        for(int i=0;i<5;i++){
            // setting beacon
            Dot11Beacon beacon;
            beacon.addr1("44:00:10:db:78:14"); // my smart phone
            beacon.ds_parameter_set(8);
            beacon.supported_rates({ 1.0f, 5.5f, 11.0f });
            beacon.rsn_information(RSNInformation::wpa2_psk());

            // difference between 5 beacons
            mac[16] += 1;
            beacon.addr2(mac);
            beacon.addr3(beacon.addr2());
            ssid[18] += 1;
            beacon.ssid(ssid);

            // send!
            radio = RadioTap() / beacon;
            sender.send(radio, iface);
        }
        mac[16] -= 5;
        ssid[18] -= 5;
        usleep(100000);
    }

}
