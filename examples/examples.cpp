#include <iostream>

#include "hekky-osc.hpp"

int main()
{
    std::cout << "Hello World!\n";

    osc::helloTest();

    std::cin.get();

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