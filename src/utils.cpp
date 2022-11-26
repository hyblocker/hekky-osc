#include "hekky/osc/utils.hpp"

namespace hekky {
	namespace osc {
		uint64_t getAlignedStringLength(const std::string& string) {
			uint64_t len = string.length() + (4 - string.length() % 4);
			if (len <= string.length()) len += 4;
			return len;
		}
	}
}