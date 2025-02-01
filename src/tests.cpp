#include <iostream>
#include <cstdlib>










// Used for testing code.
// Some macros should be used instead
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
