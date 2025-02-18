cmake_minimum_required (VERSION 3.22)

project(spm LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find_library(OPING_LIBRARY NAMES oping REQUIRED)

# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/arthursonzogni/ftxui.git
  GIT_TAG        v5.0.0
  GIT_PROGRESS   TRUE
  GIT_SHALLOW    TRUE
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(ftxui)
# ------------------------------------------------------------------------------

set(TWOL_SOURCES
  src/spm.cpp
  src/wake_on_lan.cpp
  src/spm_list.cpp
  src/tui.cpp
  src/dbg_log.cpp
  src/config.cpp
  src/utils.cpp
  # src/ping.cpp
  src/tests.cpp
)



add_executable(spm ${TWOL_SOURCES})
target_include_directories(spm PRIVATE src)

target_link_libraries(spm
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component  # Not needed for this example.
  # PRIVATE ${OPING_LIBRARY}
)
