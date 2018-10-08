package("libaco")

    set_homepage("https://github.com/hnes/libaco")
    set_description("A blazing fast and lightweight C asymmetric coroutine library.")

    set_urls("https://github.com/hnes/libaco.git")

    on_install("macosx", "linux", function (package)
        io.writefile("xmake.lua", [[
            add_rules("mode.debug", "mode.release")
            target("aco")
                set_kind("static")
                add_files("aco.c")
                add_files("acosw.S")
                add_headers("*.h")
        ]])
        import("package.tools.xmake").install(package)
    end)

