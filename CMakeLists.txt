cmake_minimum_required (VERSION 3.22)

project(twol LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
  src/twol.cpp
  src/wake_on_lan.cpp
  src/twol_list.cpp
  src/tui.cpp
  src/dbg_log.cpp
  src/config.cpp
  src/utils.cpp
  src/tests.cpp
)



add_executable(twol ${TWOL_SOURCES})
target_include_directories(twol PRIVATE src)

target_link_libraries(twol
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component  # Not needed for this example.
)
