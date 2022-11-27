#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "hekky/osc/asserts.hpp"
#include "hekky/osc/oscpacket.hpp"

namespace hekky {
	namespace osc {
		struct OscMessage : OscPacket {
		public:
			OscMessage(const std::string& address);
			~OscMessage();

			// Floating point number
			OscMessage* Push(float data);
			// Integers
			OscMessage* Push(int data);

			// ASCII Strings
			OscMessage* Push(std::string data);
			OscMessage* Push(const std::string& data);
			OscMessage* Push(char* data);
			OscMessage* Push(const char* data);
			
			// Wide strings
			OscMessage* Push(std::wstring data);
			OscMessage* Push(const std::wstring& data);
			OscMessage* Push(wchar_t* data);
			OscMessage* Push(const wchar_t* data);

			template<typename T>
			OscMessage* Push(T data) {
				HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

				// @TODO: Actually encode data

				// @NOTE: Probably going to treat generics as a binary blob
				auto type = typeid(data).name();
				std::cout << type << "\t\t" << data << std::endl;
				return this;
			}

		private:
			char* GetBytes(int& size);

		private:
			bool m_readonly;
			std::string m_address;
			std::string m_type;
			std::vector<char> m_data;
		};
	}
}