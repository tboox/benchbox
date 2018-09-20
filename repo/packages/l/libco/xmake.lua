package("libco")

    set_homepage("https://github.com/Tencent/libco")
    set_description("A coroutine library which is widely used in wechat back-end service.")

    set_urls("https://github.com/Tencent/libco.git")

    on_build("macosx", "linux", function (package)
        os.vrun("make")
    end)

    on_install("macosx", "linux", function (package)
        os.cp("*.h", package:installdir("include"))
        os.cp("lib/libcolib.a", package:installdir("lib"))
    end)
