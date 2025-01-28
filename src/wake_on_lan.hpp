#pragma once
#include <vector>
#include <string>
#include <cstdint>


// Function implementations

bool parse_mac_addr(const std::string& mac, std::vector<uint8_t>& mac_bytes);
void send_magic_pack(const std::string& mac_address, const std::string& broadcast_ip, int port = 9);
