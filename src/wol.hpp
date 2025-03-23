#pragma once

#include <string>
#include <vector>
#include <stdint.h>



class SPMWakeOnLan
{
	public:
	bool parse_mac_addr(const std::string& mac, std::vector<uint8_t>& mac_bytes);
	void SndMagicPack(const std::string& mac_address, const std::string& broadcast_ip, int port = 9);
};
