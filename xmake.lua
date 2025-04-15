add_rules("mode.debug", "mode.release")



option("ansi-escapes")
       set_default(false)
       set_showmenu(true)
       set_description("Enable ansi escapes used in coloring the text from stdout.")

option("no-msgbox")
       set_default(false)
       set_showmenu(true)
       set_description("Disable all message boxes for non graphical builds (The strings are redirected to stdout instead)")

target("spm")
    set_kind("shared")
    set_options("ansi-escapes")
    set_options("no-msgbox")
    
    if has_config("ansi-escapes") then
			 add_defines("ANSI_ESCAPES")
		end

		if has_config("no-msgbox") then
		   add_defines("NO_MSGBOX")
		end

    add_files("src/*.cpp")
    if is_plat("windows") then
        set_toolchains("msvc")
        add_syslinks("ws2_32", "user32", "iphlpapi")
    end

target("spm-serv")
    if is_plat("windows") then
        set_default(false)
    end
    set_kind("binary")
    add_files("src/server/*.c")
    add_links("procps")
    add_links("systemd")

target("test")
    -- set_enabled(false)
    set_kind("binary")
    set_options("ansi-escapes")
    set_options("no-msgbox")

    if has_config("no-msgbox") then
       add_defines("NO_MSGBOX")
    end

    if has_config("ansi-escapes") then
       add_defines("ANSI_ESCAPES")
    end
    add_files("src/*.cpp", "src/test/main.cpp")
    if is_plat("windows") then
        set_toolchains("msvc")
        add_syslinks("ws2_32", "user32", "iphlpapi")
    end

target("spm-ui")
    set_default(false)
    set_kind("binary")
    add_files("src/*.cpp", "src/frontend/frontend.cpp")
