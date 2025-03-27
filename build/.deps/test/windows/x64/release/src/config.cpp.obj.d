{
    files = {
        [[src\config.cpp]]
    },
    depfiles_format = "gcc",
    depfiles = "config.o: src\\config.cpp src\\inc/inifile-cpp/inicpp.h src\\config.hpp  src\\spm.hpp src\\utils.hpp\
",
    values = {
        "x86_64-w64-mingw32-g++",
        {
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            [[-IC:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\um]],
            [[-IC:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\shared]],
            "-fexceptions",
            "-fpermissive",
            "-DNDEBUG"
        }
    }
}