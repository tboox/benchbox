package("coroutine")

    set_homepage("https://github.com/cloudwu/coroutine")
    set_description("A asymmetric coroutine library for C.")

    set_urls("https://github.com/cloudwu/coroutine.git")

    on_install("linux", function (package)
        import("package.tools.xmake").install(package)
        os.cp("coroutine.h", package:installdir("include", "coroutine"))
    end)
