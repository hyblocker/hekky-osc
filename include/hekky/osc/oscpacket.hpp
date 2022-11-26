#pragma once

#include <stdint.h>

namespace hekky {
	namespace osc {
		struct OscPacket {

		public:

		private:
			virtual char* GetBytes(uint64_t& size) = 0;

			friend class UdpSender;
		};

		const static uint64_t OSC_MINIMUM_PACKET_BYTES = 8;
	}
}