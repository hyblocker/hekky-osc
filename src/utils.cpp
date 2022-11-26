#include "hekky/osc/utils.hpp"

namespace hekky {
	namespace osc {
		uint64_t GetAlignedStringLength(const std::string& string) {
			uint64_t len = string.length() + (4 - string.length() % 4);
			if (len <= string.length()) len += 4;
			return len;
		}

		bool IsLittleEndian() {
			union {
				uint32_t i;
				char c[4];
			} endianCheck = { 0x01020304 };

			return endianCheck.c[0] != 1;
		}

		uint32_t SwapInt32(uint32_t num) {
			return static_cast<std::uint32_t>((num << 24) | ((num << 8) & 0x00FF0000) | ((num >> 8) & 0x0000FF00) | (num >> 24));
		}

		float SwapFloat32(float num) {

			union {
				float f;
				uint32_t ui32;
			} swapper = { num };

			swapper.ui32 = SwapInt32(swapper.ui32);
			return swapper.f;
		}
	}
}