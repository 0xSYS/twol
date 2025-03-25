#include <iostream>





#include "../spm.hpp"
#include "../config.hpp"
#include "../wol.hpp"
#include "../utils.hpp"
#include "../dbg_log.hpp"
#include "../globals.hpp"




SPM spm_cls;

void Test1()
{
	std::cout << "Test1() -> SPM::Init()\n";
	spm_cls.Init();
}




int main(int argc, char * argv[])
{
	std::cout << "- - - - SPM BACKEND TESTS - - - - \n\n\n\n";
	Test1();
	return 0;
}
