package("libgo")

    set_homepage("https://github.com/yyzybb537/libgo")
    set_description("Go-style concurrency in C++11.")

    set_urls("https://github.com/yyzybb537/libgo.git")

    if is_host("macosx", "linux") then
        add_deps("cmake")
    end

    on_install("macosx", "linux", function (package)
        import("package.tools.cmake").install(package)
    end)

