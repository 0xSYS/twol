

#include <iostream>




// #define DEVEL


#include "config.hpp"
#include "wake_on_lan.hpp"
#include "tui.hpp"
#include "tests.h"
#include "utils.hpp"





// The entry point

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
    // send_magic_pack(mac_addres_cli, broadcast_ip_cli); // Triggers power on event trough the lan (wake on lan function which relies on the magick packet thing)
    tui_main();      // Render the ascii "gui"
    // tui_tests();  // Used for developing the tui
    // test_stuff(); // Used only for testing most of the backend
    // twol_init();  // Initialise twol (read config and computer lists)
   
   return 0;
}



/*
Todo:
* Windows compatibility for:
    - File path locations
    - Wake on lan windows implementation





====[ New Ideeas ]====
# List restriction (Only specific users can manage the servers or computers by being prompt with a password)
# Wake on lan time schedule
# IPMI Support
# CLI Support:
  Example usage: twol [options] <pc name / pc number>
  options:
  -on    --power_on
  -off   --power_off
  -ls    --list
  -pstat --power_status
  -rm    --remove
  -add
*/
