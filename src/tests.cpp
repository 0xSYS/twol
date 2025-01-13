#include <iostream>
#include <cstdlib>











void test_stuff()
{
  // blah blah
  const char * homeDir = std::getenv("HOME");

  if(homeDir)
  {
    std::cout << "Dir " << homeDir << "\n";
  }
  else
  {
    std::cout << "No home dir lol\n";
  }
}
