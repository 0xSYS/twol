{
    files = {
        [[build\.objs\spm\windows\x64\release\src\config.cpp.obj]],
        [[build\.objs\spm\windows\x64\release\src\dev_detect.cpp.obj]],
        [[build\.objs\spm\windows\x64\release\src\spm.cpp.obj]],
        [[build\.objs\spm\windows\x64\release\src\spm_api.cpp.obj]],
        [[build\.objs\spm\windows\x64\release\src\spm_list.cpp.obj]],
        [[build\.objs\spm\windows\x64\release\src\utils.cpp.obj]],
        [[build\.objs\spm\windows\x64\release\src\wol.cpp.obj]]
    },
    values = {
        [[C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.39.33519\bin\HostX64\x64\link.exe]],
        {
            "-nologo",
            "-machine:x64",
            "/opt:ref",
            "/opt:icf",
            "ws2_32.lib",
            "user32.lib"
        }
    }
}