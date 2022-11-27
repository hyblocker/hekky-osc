# Hekky OSC

An OSC Library for C++, based on [CoreOSC](https://github.com/PaciStardust/CoreOSC-UTF8).

### Motivation

<p align="center">
<img alt="XKCD 927 - Standards" src="https://user-images.githubusercontent.com/7695629/204110847-b113dea6-32cc-48e5-8b40-8e1f36ab085b.png">
</p>

> [XKCD 927](https://xkcd.com/927/)

OSC libraries in C++ suck. The APIs are either extremely verbose, the library has too many dependencies and is a nightmare to get working, or difficult to use without leaking memory.

I'm also using this library as an excuse to learn C++ better and improve my ability to write good C++ code.

### License

This project is licensed under the MIT license. CoreOSC is also licensed under the MIT license.

---

# Usage

```cpp
#include <iostream>

#include "hekky-osc.hpp"

int main()
{
    // Open a UDP socket, pointing to localhost on port 9000
    auto udpSender = hekky::osc::UdpSender("127.0.0.1", 9000);

    // Pushes a integer "12" to /osc/test
    auto message = hekky::osc::OscMessage("/osc/test");
    message.Push(12);
    udpSender.Send(message);

    // Pushes a string "Hello World!" to /osc/some/endpoint
    auto message2 = hekky::osc::OscMessage("/osc/some/endpoint");
    message2.Push("Hello World!");
    udpSender.Send(message2);

    // Pushes a 3-component float to /osc/vector/endpoint
    // This is one way you can represent vectors using OSC
    auto serialPacking = hekky::osc::OscMessage("/osc/vector/float32");
    serialPacking.Push(1.4142135624f); // sqrt(2)
    serialPacking.Push(3.1415926536f); // pi
    serialPacking.Push(2.7182818285f); // e
    udpSender.Send(serialPacking);

    // Alternatively, you can encode the same message like this:
    auto chainPacking = hekky::osc::OscMessage("/osc/vector/float32");
    chainPacking.Push(1.4142135624f)->Push(3.1415926536f)->Push(2.7182818285f);
    udpSender.Send(chainPacking);

    // Closing it manually isn't needed, it gets closed via the destructor automatically!
    // udpSender.Close();

    std::cout << "Done!\n";
}
```

## Supported platforms

| Platform | Supported |
| -------- | --------- |
| Windows  | ✅         |
| MacOS    | ❌         |
| Linux    | ❌         |
