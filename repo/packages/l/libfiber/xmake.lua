package("libfiber")

    set_homepage("http://zsxxsz.iteye.com/")
    set_description("The high performance coroutine library for Linux/FreeBSD/MacOS/Windows.")

    set_urls("https://github.com/acl-dev/libfiber.git")

    on_build(function (package)
        import("package.builder.xmake").build(package)
    end)

    on_install(function (package)
        import("package.builder.xmake").install(package)
    end)
