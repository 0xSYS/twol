

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
    #ifdef DEVEL
      if(argc != 1) 
      {
          std::cout << argv[0] <<  "No Args!\n";
          return 1;
      }

      std::string mac_addres_cli = argv[1];
      std::string broadcast_ip_cli = argv[2];
      send_magic_pack(mac_addres_cli, broadcast_ip_cli); // Triggers power on event trough the lan (wake on lan function which relies on the magick packet thing)
    #endif
    

    #ifdef TUI_TESTS
      tui_tests();  // Used for developing the tui
    #else
      tui_main();
    #endif

    #ifdef DEVEL
      test_stuff(); // Used only for testing most of the backend
    #else
     twol_init();  // Initialise twol (read config and computer lists)
    #endif


    /*
    Most testing stuff has been moved to tests.cpp
    */

    

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
