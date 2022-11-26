#pragma once

#include "hekky/osc/platform.hpp"
#include "hekky/osc/asserts.hpp"

#include <string>

#ifdef HEKKYOSC_WINDOWS

// Winsock API
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

// Tell the linker to link to the winsock library
#pragma comment(lib, "Ws2_32.lib")

#endif

namespace hekky {
	namespace osc {

		typedef enum {
			UDP,
			TCP,
		} OSC_NetworkProtocol;

		/// <summary>
		/// A network device which sends packets to the specified destination using UDP.
		/// </summary>
		class UdpSender {
		public:
			/// <summary>
			/// Opens a UDP socket connection.
			/// </summary>
			/// <param name="ipAddress">Destination IP Address</param>
			/// <param name="port">Destination port</param>
			UdpSender(const std::string& ipAddress, uint32_t port, OSC_NetworkProtocol protocol = OSC_NetworkProtocol::UDP);
			/// <summary>
			/// Destroys this UDP socket connection, if it's alive.
			/// </summary>
			~UdpSender();

			/// <summary>
			/// Closes this UDP socket connection. Sending messages after closing this will do nothing.
			/// </summary>
			void Close();

			/// <summary>
			/// Sends a buffer of data over this UDP socket.
			/// </summary>
			/// <param name="data">A pointer to the buffer's data</param>
			/// <param name="size">The size of the buffer</param>
			void Send(char* data, uint64_t size);

		private:
			bool m_isAlive;
			std::string m_address;
			uint32_t m_port;
#ifdef HEKKYOSC_WINDOWS
			WSADATA m_wsaData;
			SOCKET m_nativeSocket;

			sockaddr_in m_destinationAddress;
			sockaddr_in m_localAddress;

#endif
		};
	}
}