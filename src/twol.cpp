#include <iostream>

#include "config.hpp"
#include "wake_on_lan.hpp"
#include "tui.hpp"
#include "tests.h"
#include "utils.hpp"



int main(int argc, char **argv) 
{
    // if(argc != 1) 
    // {
    //     std::cout << argv[0] <<  "No Args!\n";
    //     return 1;
    // }
    // cfg Configuration;
    // Configuration.pc_status_mpack = true;
    
    // twol_cfg_write(Configuration);

    // std::cout << "twol.conf written\n";

    // std::string mac_addres_cli = argv[1];
    // std::string broadcast_ip_cli = argv[2];
    // send_magic_pack(mac_addres_cli, broadcast_ip_cli);
    tui_main();
    // tui_tests();
    // test_stuff();
    // twol_init();
   
   return 0;
}
