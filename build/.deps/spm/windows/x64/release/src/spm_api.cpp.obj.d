{
    files = {
        [[src\spm_api.cpp]]
    },
    depfiles_format = "gcc",
    depfiles = "spm_api.o: src\\spm_api.cpp src\\spm.hpp src\\api_utils.h src\\wol.hpp\
",
    values = {
        "x86_64-w64-mingw32-g++",
        {
            "-O3",
            "-std=c++17",
            [[-IC:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\um]],
            [[-IC:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\shared]],
            "-fexceptions",
            "-fpermissive",
            "-DNDEBUG"
        }
    }
}