

#include <iostream>




 #define DEVEL
// #define TUI_TESTS


#include "config.hpp"
#include "wake_on_lan.hpp"
#include "tui.hpp"
#ifdef DEVEL
  #include "tests.h"
#endif
#include "utils.hpp"
#include "ping.hpp"





// The entry point

int main(int argc, char **argv) 
{
    #ifdef SPM_CLI
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
      // tui_main();
    #endif

    #ifdef DEVEL
      test_stuff(); // Used only for testing most of the backend
   // #else
      spm_init();  // Initialise twol (read config and computer lists)
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

  Todo:
  [Restricted session]
  !!! IMPORTANT !!! Working on full IPMI support
  - Custom lan packet (bidirectional transmission on local network area) used to get all available pc / servers and creating temporarry list on the host controller server
  * Packet pattern: (From host sender)"isSPM" Checks if the SPM daemon runs.
                    (From available host) "isSPM isIPMI isWOL" Checks for IPMI support or Wake On Lan Support
  - Secure the transmission between servers / computers when sending custom eth packet (Requires openSSL)                    
  - At startup get all available PCs or servers
  - Ask for list creation (A prompt) containing all servers / or discovered pcs available for remote connections via SSH
  - Get available users with the right permissions
  - Verify all power permissions for specific users
  - (Option / Feature) Provide ip or ip s from all servers / computers
  - Verify specific server  / computer if it's available for connections (Check if a pc / server is online of offline)
  - Separated component of the software: A linux service (Daemon) that monitors the activity of each signed server or computer
  ** Possible total rename to SPM (Server Power Management)
*/
