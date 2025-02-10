

#include <iostream>




// #define DEVEL
// #define TUI_TESTS


#include "config.hpp"
#include "wake_on_lan.hpp"
#include "tui.hpp"
#ifdef DEVEL
  #include "tests.h"
#endif
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
    tui_main();
          // Render the ascii "gui"
    #ifdef TUI_TESTS
      tui_tests();  // Used for developing the tui
    #endif
    // test_stuff(); // Used only for testing most of the backend
    // twol_init();  // Initialise twol (read config and computer lists)

    
    cfg test_cfg;
    /*
    test_cfg.cli_mode = true;
    test_cfg.restrict_mode = false;
    test_cfg.restrict_autolink = false;
    test_cfg.debug_log = true;
    test_cfg.pc_status_mpack = true;

    twol_cfg_write(test_cfg);
    */
    /*test_cfg = twol_cfg_read();

    std::cout << "CLI mode: " << test_cfg.cli_mode << "\n";
    std::cout << "Debug Log: " << test_cfg.debug_log << "\n";
    std::cout << "PC Status: " << test_cfg.pc_status_mpack << "\n";
    std::cout << "Restrict Autolink: " << test_cfg.restrict_autolink << "\n";
    std::cout << "Restrict Mode: " << test_cfg.restrict_mode << "\n";*/
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
# Restrict mode timeout (enable / disable only from cfg file)
# Custom setting for restrict mode (1 min, 10 min or anything else)
# Add / Remove specific users for restricted mode
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
