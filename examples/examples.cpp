#include <iostream>

#include "hekky-osc.hpp"

int main()
{
    // Open a UDP socket, pointing to localhost on port 9000
    auto udpSender = hekky::osc::UdpSender("127.0.0.1", 9000);

    auto message = hekky::osc::OscMessage("/osc/test");
    message.Push(12);
    udpSender.Send(message);

    auto message2 = hekky::osc::OscMessage("/osc/some/endpoint");
    message2.Push("Hello World!");
    udpSender.Send(message2);

    auto message3 = hekky::osc::OscMessage("/osc/vector/endpoint");
    message3.Push(1.4142135624f); // sqrt(2)
    message3.Push(3.1415926536f); // pi
    message3.Push(2.7182818285f); // e
    udpSender.Send(message3);

    // Closing it manually isn't needed, it gets closed via the destructor automatically!
    // udpSender.Close();

    std::cout << "Done!\n";
}