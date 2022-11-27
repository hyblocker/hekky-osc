#include <iostream>

#include "hekky-osc.hpp"

int main()
{
    srand(time(0));

    // Open a UDP socket, pointing to localhost on port 9000
    auto udpSender = hekky::osc::UdpSender("127.0.0.1", 9000);

    auto message3 = hekky::osc::OscMessage("/test/one");
    message3.Push(12);
    udpSender.Send(message3);

    auto message = hekky::osc::OscMessage("/tracking/trackers/1/position");
    message.Push( (1000.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1001.f - 1000.f)))) / 1000.f );
    message.Push( (1000.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1001.f - 1000.f)))) / 1000.f );
    message.Push( (1000.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1001.f - 1000.f)))) / 1000.f );
    udpSender.Send(message);

    auto message2 = hekky::osc::OscMessage("/osc/some/endpoint");
    message2.Push("Wonderhoy!");
    udpSender.Send(message2);

    auto message4 = hekky::osc::OscMessage("/osc/some/endpoint");
    message4.Push(5);
    udpSender.Send(message4);

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