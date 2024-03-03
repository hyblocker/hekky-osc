hekky_osc: examples/examples.cpp src/oscmessage.cpp include/hekky/osc/oscpacket.cpp src/udpsender.cpp src/utils.cpp
	g++ -g -Wall -o a.out examples/examples.cpp src/oscmessage.cpp include/hekky/osc/oscpacket.cpp src/udpsender.cpp src/utils.cpp -I include/hekky/osc -I include

