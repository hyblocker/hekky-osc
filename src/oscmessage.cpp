#include "hekky/osc/oscmessage.hpp"
#include "hekky/osc/utils.hpp"
#include <math.h>

namespace hekky {
	namespace osc {
		OscMessage::OscMessage(const std::string& address)
			: m_address(address), m_type(","), m_readonly(false)
		{
			m_data.reserve(constants::OSC_MINIMUM_PACKET_BYTES);
		}

		OscMessage::~OscMessage() {
			m_data.clear();
		}

		OscMessage* OscMessage::Push(float data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			if (isinf(data)) {
				m_type += "I";
			} else {
				union {
					float f;
					char c[4];
				} primitiveLiteral = { data };

				if (utils::IsLittleEndian()) {
					primitiveLiteral.f = utils::SwapFloat32(data);
				}

				m_data.insert(m_data.end(), primitiveLiteral.c, primitiveLiteral.c + 4);
				m_type += "f";
			}
			return this;
		}

		OscMessage* OscMessage::Push(int data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			union {
				int i;
				char c[4];
			} primitiveLiteral = { data };

			if (utils::IsLittleEndian()) {
				primitiveLiteral.i = utils::SwapInt32(data);
			}

			m_data.insert(m_data.end(), primitiveLiteral.c, primitiveLiteral.c + 4);
			m_type += "i";
			return this;
		}

		OscMessage* OscMessage::Push(std::string data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			std::copy(data.begin(), data.end(), std::back_inserter(m_data));
			m_data.insert(m_data.end(), utils::GetAlignedStringLength(data) - data.length(), 0);
			m_type += "s";
			return this;
		}

		OscMessage* OscMessage::Push(const std::string& data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			std::copy(data.begin(), data.end(), std::back_inserter(m_data));
			m_data.insert(m_data.end(), utils::GetAlignedStringLength(data) - data.length(), 0);
			m_type += "s";
			return this;
		}

		OscMessage* OscMessage::Push(const char* data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			m_data.insert(m_data.end(), data, data + strlen(data));
			m_data.insert(m_data.end(), utils::GetAlignedStringLength(data) - strlen(data), 0);
			m_type += "s";
			return this;
		}

		OscMessage* OscMessage::Push(char* data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			m_data.insert(m_data.end(), data, data + strlen(data));
			m_data.insert(m_data.end(), utils::GetAlignedStringLength(data) - strlen(data), 0);
			m_type += "s";
			return this;
		}

		OscMessage* OscMessage::Push(std::wstring data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			std::copy(data.begin(), data.end(), std::back_inserter(m_data));
			m_data.insert(m_data.end(), utils::GetAlignedStringLength(data) - data.length(), 0);
			m_type += "s";
			return this;
		}

		OscMessage* OscMessage::Push(const std::wstring& data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			std::copy(data.begin(), data.end(), std::back_inserter(m_data));
			m_data.insert(m_data.end(), utils::GetAlignedStringLength(data) - data.length(), 0);
			m_type += "s";
			return this;
		}

		OscMessage* OscMessage::Push(const wchar_t* data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			m_data.insert(m_data.end(), data, data + wcslen(data));
			m_data.insert(m_data.end(), utils::GetAlignedStringLength(data) - wcslen(data), 0);
			m_type += "s";
			return this;
		}

		OscMessage* OscMessage::Push(wchar_t* data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			m_data.insert(m_data.end(), data, data + wcslen(data));
			m_data.insert(m_data.end(), utils::GetAlignedStringLength(data) - wcslen(data), 0);
			m_type += "s";
			return this;
		}

		char* OscMessage::GetBytes(int& size) {
			std::vector<char> headerData;

			// Append address
			std::copy(m_address.begin(), m_address.end(), std::back_inserter(headerData));
			headerData.insert(headerData.end(), utils::GetAlignedStringLength(m_address) - m_address.length(), 0);

			// Append types
			std::copy(m_type.begin(), m_type.end(), std::back_inserter(headerData));
			headerData.insert(headerData.end(), utils::GetAlignedStringLength(m_type) - m_type.length(), 0);

			// Add header to start of data block
			m_data.insert(m_data.begin(), headerData.begin(), headerData.end());
			
			// Lock this packet
			m_readonly = true;
			size = static_cast<int>(m_data.size());
			return m_data.data();
		}
	}
}