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

			void Push(float data);
			void Push(int data);

			template<typename T>
			void Push(T data) {
				HEKKYOSC_ASSERT(m_readonly == false, "Cannot write to a message packet once sent to the network! Construct a new message instead.");

				// @TODO: Actually encode data

				// @NOTE: Probably going to treat generics as a binary blob
				auto type = typeid(data).name();
				std::cout << type << "\t\t" << data << std::endl;
			}

		private:
			char* GetBytes(uint64_t& size);

		private:
			bool m_readonly;
			std::string m_address;
			std::string m_type;
			std::vector<char> m_data;
		};
	}
}