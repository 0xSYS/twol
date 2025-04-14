#include <iostream>





#include "../spm.hpp"
#include "../config.hpp"
#include "../wol.hpp"
#include "../dev_detect.hpp"
#include "../utils.hpp"
#include "../dbg_log.hpp"
#include "../globals.hpp"
#include "../spm_list.hpp"
#include "../sckt_io.hpp"




SPM spm_cls;
SPMWakeOnLan wol;
SPMDetect sdetect;
SPMList spm_lst;
SPM_SocketIO sckt_io;




void Test1()
{
	std::cout << "Test1() -> SPM::Init()\n";
	spm_cls.Init();
}

void Test2()
{
	std::cout << "Test2() -> SPMWakeOnLan::SndMagicPack()\n";
	wol.SndMagicPack("1c:6f:65:c2:e8:2f", "192.168.1.255");
	wol.SndMagicPack("6c:f0:49:a1:d9:e6", "192.168.1.255");
	// Previous: 1c:6f:65:c2:e8:2f
	//6c:f0:49:a1:d9:e6
}

void Test3()
{
	SPMDebug dbg;
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

void Test4()
{
	SPMDebug dbg;
	std::cout << "Test4() -> Log testing\n";
	dbg.Log(SPMDebug::Warn, "Some info", " And another string");
}

void Test5()
{
	SPMDebug dbg;
	dbg.MsgBoxLog(SPMDebug::Info, "Arg 1 ", "Arg 2 ", 5);
	dbg.MsgBoxLog(SPMDebug::Success, "Success test " , "And another stringy string ", 48);
	dbg.MsgBoxLog(SPMDebug::Warn, "Warning test ", "yet anoter text and a number idk ", 152);
	dbg.MsgBoxLog(SPMDebug::Err, "This is some error ", " things work ok ig ", 196);
}

void Test6()
{
	std::vector<std::string> dummy = sdetect.CreateIP_Table();
}

void Test7()
{
	std::vector<SPMList::computer> someList = spm_lst.ReadComputerList();

	for(int i = 0; i < someList.size(); i++)
	{
		std::cout << someList[i].name << " " << someList[i].broadcastIP << " " << someList[i].broadcastIP << " " << someList[i].macAddr << "\n";

	}
}

void Test8()
{
	SPMDebug dbg;
	for(int i = 0; i < 5; i++)
	{
		dbg.Log(SPMDebug::Info, "Updating stuff");
	}
}

void Test9()
{
	std::cout << "Power actions test\n";
	sckt_io.SndPowerAction(SPM_SocketIO::Poweroff, "192.168.1.102");
	// sckt_io.SndPowerAction(SPM_SocketIO::Reboot, "192.168.1.34");
}


int main(int argc, char * argv[])
{
	std::cout << "- - - - SPM BACKEND TESTS - - - - \n\n\n\n";
	// Test1(); // Linux Pass
	// Test2(); // Linux, Windows Pass
	// Test3(); // 
	// Test4(); // All pass
	// Test5();
  // Test6();
	// Test7();
	// Test8();
  Test9();
	return 0;
}


/*
Temp stuff

https://github.com/MichaelDipperstein/ezini/blob/master/sample.c
https://github.com/benhoyt/inih/tree/master
https://github.com/compuphase/minIni/blob/master/dev/test.c
*/
