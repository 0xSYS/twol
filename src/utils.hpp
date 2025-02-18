#pragma once

#include <cstdlib>
#include <string>

#include "config.hpp"






inline std::string homeDir = std::getenv("HOME");
std::string get_current_date();



void spm_init();
void spm_power_on(std::string name);
