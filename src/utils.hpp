#pragma once

#include <cstdlib>
#include <string>

#include "config.hpp"






inline std::string homeDir = std::getenv("HOME");
std::string get_current_date();



void twol_init();
void twol_power_on(std::string name);
