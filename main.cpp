#include <iostream>
#include <unistd.h>

#include <tins/tins.h>

using namespace Tins;

int main(int argc, char *argv[])
{

    Dot11Beacon beacon;
    beacon.addr1("44:00:10:db:78:14"); // my smart phone
    beacon.addr2("44:00:10:00:00:01");
    beacon.addr3(beacon.addr2());


    beacon.ssid("길길짱잘생김");
    beacon.ds_parameter_set(8);
    beacon.supported_rates({ 1.0f, 5.5f, 11.0f });
    beacon.rsn_information(RSNInformation::wpa2_psk());

    RadioTap radio = RadioTap() / beacon;
    //PacketWriter writer("output.pcap", PacketWriter::RADIOTAP);
    //writer.write(radio);

    PacketSender sender;
    NetworkInterface iface("wlan0");

    while(true){
        sender.send(radio, iface);
        usleep(100000);
    }

}
