set_toolchains("mingw")

if is_plat("windows") then
    

    add_cflags("-fpermissive", {force = true})
    add_cxxflags("-fpermissive", {force = true})

    set_toolset("cc", "x86_64-w64-mingw32-gcc")
    set_toolset("cxx", "x86_64-w64-mingw32-g++")
    set_toolset("ld", "x86_64-w64-mingw32-ld")

    -- Ensure correct Windows SDK directories are included
    add_includedirs("C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/um", {force = true})
    add_includedirs("C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/shared", {force = true})
    add_ldflags("-L/C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64", {force = true})
    add_ldflags("-lws2_32", {force = true})
    add_ldflags("-lIphlpapi", {force = true})
end






add_rules("mode.debug", "mode.release")

target("spm")
    set_kind("shared")
    add_files("src/*.cpp")
    set_languages("c++17")
    if is_plat("windows") then
        --toolchain("mingw")
        -- add_syslinks("ws2_32")
        -- add_syslinks("user32")
        add_ldflags("-luser32", {force = true}) -- Ensure user32 is linked in MinGW
        add_ldflags("-lws2_32", {force = true}) -- Link WS2_32.lib
        -- add_ldflags("User32.lib", {force = true}) -- Forces linking User32.lib
        -- add_ldflags("-lu user32")
        -- add_defines("WIN32_LEAN_AND_MEAN")
    end

target("test")
    -- set_enabled(false)
    set_kind("binary")
    add_files("src/*.cpp")
    add_files("src/test/main.cpp")

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

