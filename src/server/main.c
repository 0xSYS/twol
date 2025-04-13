#include <stdio.h>


#include "dbg.h"
#include "proc_manager.h"
#include "power_funcs.h"




void TestingStuff()
{
    // sdfadsfd
    Log(Info, "Info Log");
    Log(Success, "Success Log");
    Log(Warn, "Warn Log");
    Log(Err, "Error Log");
}



int main(int argc, char * argv[])
{
    // Do stuff here
    TestingStuff();
    /*
    CheckRuningProc("helix");
    CheckRuningProc("zsh");
    CheckRuningProc("tmux");
    */
    // SysReboot();
    SysPowerOff();
	return 0;
}
