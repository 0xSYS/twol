#include <iostream>
#include <cstdlib>
#include <numeric>

#include "config.hpp"
#include "ping.hpp"






cfg writeCfgTest;
cfg readCfgTest;

// Used for testing code.
void test_stuff()
{
  // blah blah

  std::cout << "test_stuff()\n";
  /*
  const char * homeDir = std::getenv("HOME");

  if(homeDir)
  {
    std::cout << "Dir " << homeDir << "\n";
  }
  else
  {
    std::cout << "No home dir lol\n";
  }*/
  /*
  |---------------------------|
  | Configuration assign test |
  |---------------------------|
  */
  
  writeCfgTest.cli_mode = true;
  writeCfgTest.restrict_mode = false;
  writeCfgTest.restrict_autolink = false;
  writeCfgTest.restrict_timeout = true;
  writeCfgTest.debug_log = true;
  writeCfgTest.rescrict_time_span = 5;
  writeCfgTest.pc_status_mpack = false;
  writeCfgTest.restr_users = { "Someone", "SomeoneElse", "A dude"};
  writeCfgTest.restr_list_path = "/home/someone/get/the/path/to/file/lol";

  spm_cfg_write(writeCfgTest);

  /*
  |-----------------------|
  | Configuration Reading |
  |-----------------------|
  */
  /*readCfgTest = spm_cfg_read(); // Read and assign the contents of the configuration file to this structure


  int restrUsrsIndex = sizeof(readCfgTest.restr_users);

  // And print to stdout the freshly updated config structure
  std::cout << "CLI Mode:             " << readCfgTest.cli_mode           << "\n";
  std::cout << "Restrict Mode:        " << readCfgTest.restrict_mode      << "\n";
  std::cout << "Restrict Autolink:    " << readCfgTest.restrict_autolink  << "\n";
  std::cout << "Restrict Timeout:     " << readCfgTest.restrict_timeout   << "\n";
  std::cout << "Debug Log:            " << readCfgTest.debug_log          << "\n";
  std::cout << "Restrict Timespan:    " << readCfgTest.rescrict_time_span << "\n";
  std::cout << "PC Status:            " << readCfgTest.pc_status_mpack    << "\n";
  std::cout << "Restricted List Path: " << readCfgTest.restr_list_path    << "\n";
  std::cout << "Restricted Users: \n";
  for(int i = 0; i < restrUsrsIndex; i++)
  {
    std::cout << readCfgTest.restr_users[i] << "\n";
  }*/

  // spm_ping("8.8.8.8");
}
