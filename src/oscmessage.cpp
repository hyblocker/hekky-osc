#include "hekky/osc/oscmessage.hpp"
#include "hekky/osc/utils.hpp"

namespace hekky {
	namespace osc {
		OscMessage::OscMessage(const std::string& address)
			: m_address(address), m_type(","), m_readonly(false)
		{
			m_data.reserve(OSC_MINIMUM_PACKET_BYTES);
		}

		OscMessage::~OscMessage() {
			m_data.clear();
		}

		void OscMessage::Push(float data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			union {
				float f;
				char c[4];
			} primitiveLiteral = { data };

			if (IsLittleEndian()) {
				primitiveLiteral.f = SwapFloat32(data);
			}

			m_data.insert(m_data.end(), primitiveLiteral.c, primitiveLiteral.c + 4);
			m_type += "f";
		}

		void OscMessage::Push(int data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			union {
				int i;
				char c[4];
			} primitiveLiteral = { data };

			if (IsLittleEndian()) {
				primitiveLiteral.i = SwapInt32(data);
			}

			m_data.insert(m_data.end(), primitiveLiteral.c, primitiveLiteral.c + 4);
			m_type += "i";
		}

		void OscMessage::Push(std::string data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			std::copy(data.begin(), data.end(), std::back_inserter(m_data));
			m_data.insert(m_data.end(), GetAlignedStringLength(data) - data.length(), 0);
			m_type += "s";
		}

		void OscMessage::Push(const std::string& data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			std::copy(data.begin(), data.end(), std::back_inserter(m_data));
			m_data.insert(m_data.end(), GetAlignedStringLength(data) - data.length(), 0);
			m_type += "s";
		}

		void OscMessage::Push(const char* data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			m_data.insert(m_data.end(), data, data + strlen(data));
			m_data.insert(m_data.end(), GetAlignedStringLength(data) - strlen(data), 0);
			m_type += "s";
		}

		void OscMessage::Push(char* data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			m_data.insert(m_data.end(), data, data + strlen(data));
			m_data.insert(m_data.end(), GetAlignedStringLength(data) - strlen(data), 0);
			m_type += "s";
		}

		void OscMessage::Push(std::wstring data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			std::copy(data.begin(), data.end(), std::back_inserter(m_data));
			m_data.insert(m_data.end(), GetAlignedStringLength(data) - data.length(), 0);
			m_type += "s";
		}

		void OscMessage::Push(const std::wstring& data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			std::copy(data.begin(), data.end(), std::back_inserter(m_data));
			m_data.insert(m_data.end(), GetAlignedStringLength(data) - data.length(), 0);
			m_type += "s";
		}

		void OscMessage::Push(const wchar_t* data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			m_data.insert(m_data.end(), data, data + wcslen(data));
			m_data.insert(m_data.end(), GetAlignedStringLength(data) - wcslen(data), 0);
			m_type += "s";
		}

		void OscMessage::Push(wchar_t* data) {
			HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

			m_data.insert(m_data.end(), data, data + wcslen(data));
			m_data.insert(m_data.end(), GetAlignedStringLength(data) - wcslen(data), 0);
			m_type += "s";
		}

		char* OscMessage::GetBytes(int& size) {
			std::vector<char> headerData;

			// Append address
			std::copy(m_address.begin(), m_address.end(), std::back_inserter(headerData));
			headerData.insert(headerData.end(), GetAlignedStringLength(m_address) - m_address.length(), 0);

			// Append types
			std::copy(m_type.begin(), m_type.end(), std::back_inserter(headerData));
			headerData.insert(headerData.end(), GetAlignedStringLength(m_type) - m_type.length(), 0);

			// Add header to start of data block
			m_data.insert(m_data.begin(), headerData.begin(), headerData.end());
			
			// Lock this packet
			m_readonly = true;
			size = m_data.size();
			return m_data.data();
		}
	}
}