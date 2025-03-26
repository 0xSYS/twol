#include <iostream>





#include "../spm.hpp"
#include "../config.hpp"
#include "../wol.hpp"
#include "../utils.hpp"
#include "../dbg_log.hpp"
#include "../globals.hpp"




SPM spm_cls;
SPMWakeOnLan wol;

void Test1()
{
	std::cout << "Test1() -> SPM::Init()\n";
	spm_cls.Init();
}

void Test2()
{
	std::cout << "Test2() -> SPMWakeOnLan::SndMagicPack()\n";
	wol.SndMagicPack("1c:6f:65:c2:e8:2f", "192.168.1.255");
}

void Test3()
{
	std::vector<uint8_t> byte_array;
	std::cout << "Test3() -> SPMWakeOnLan::parse_mac_addr()\n";
	if(wol.parse_mac_addr("1c:6f:65:c2:e8:2f", byte_array))
	{
		dbg.Log(SPMDebug::Success, "Mac address parsed successfully");
	}
	else
	{
		dbg.Log(SPMDebug::Err, "Failed to parse mac address");
	}
}


int main(int argc, char * argv[])
{
	std::cout << "- - - - SPM BACKEND TESTS - - - - \n\n\n\n";
	// Test1(); // Linux Pass
	// Test2(); // Linux Pass
	Test3(); // 
	return 0;
}
