#include <iostream>

#include "hekky-osc.hpp"

int main()
{
    // Open a UDP socket, pointing to localhost on port 9000
    auto udpSender = hekky::osc::UdpSender("127.0.0.1", 9000);

    // Temporary OSC packet, we will have methods to construct these later
    constexpr char buffer[] = {
        47, 116, 101, 115, 116, 47, 111, 110, 101, 0, 0, 0, // /test/one
        44, 105, 0, 0,                                      // ,i
        00, 00, 00, 12,                                     // 12
    };
    udpSender.Send((char*)buffer, sizeof(buffer));

    // Closing it manually isn't needed, it gets closed via the destructor automatically!
    // udpSender.Close();

    std::cout << "Done!\n";

    // Goal is to be able to do something similar with relative ease.
    /*
    
    internal static class VrcOscHell
    {
        private static readonly string[] _endpoints = new string[]
        {
            "/tracking/trackers/1/position",
            "/tracking/trackers/1/rotation",
            "/tracking/trackers/2/position",
            "/tracking/trackers/2/rotation",
            "/tracking/trackers/3/position",
            "/tracking/trackers/3/rotation",
            "/tracking/trackers/head/position",
            "/tracking/trackers/head/rotation"
        };

        internal static void Start()
        {
            var sender = new UDPSender("127.0.0.1", 9000);
            var r = new Random();

            while(true)
            {
                for (int i = 0; i < _endpoints.Length; i++)
                {
                    OscMessage packet = (i & 1) == 1
                        ? new(_endpoints[i], r.Next(360), r.Next(360), r.Next(360))
                        : new(_endpoints[i], r.Next(-1000, 1001) / 1000f, r.Next(-1000, 1001) / 1000f, r.Next(-1000, 1001) / 1000f);
                    sender.Send(packet);
                    Thread.Sleep(50);
                }
            }
        }
    }

    */
}