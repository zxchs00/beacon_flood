#include <iostream>
#include <unistd.h>

#include <tins/tins.h>

using namespace Tins;
using namespace std;

int main(int argc, char *argv[])
{
    char mac[18] = "00:07:89:00:00:00";
    char ssid[20] = "길길짱잘생김0";
    cout << strlen(ssid);

    Dot11Beacon beacon;
    beacon.addr1("44:00:10:db:78:14"); // my smart phone
    //beacon.addr1(Dot11::BROADCAST);
    beacon.addr2(mac);
    beacon.addr3(beacon.addr2());
    beacon.ssid("길길짱잘생김");
    beacon.ds_parameter_set(8);
    beacon.supported_rates({ 1.0f, 5.5f, 11.0f });
    beacon.rsn_information(RSNInformation::wpa2_psk());

    RadioTap radio;// = RadioTap() / beacon;
    //PacketWriter writer("output.pcap", PacketWriter::RADIOTAP);
    //writer.write(radio);

    PacketSender sender;
    NetworkInterface iface("wlan0");

    while(true){
        for(int i=0;i<5;i++){
            mac[16] += 1;
            beacon.addr2(mac);
            beacon.addr3(beacon.addr2());
            ssid[18] += 1;
            beacon.ssid();

            radio = RadioTap() / beacon;
            sender.send(radio, iface);
        }
        mac[16] -= 5;
        ssid[18] -= 5;
        usleep(100000);
    }

}
