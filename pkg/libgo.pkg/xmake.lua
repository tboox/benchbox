-- add libgo package
option("libgo")

    -- show menu
    set_showmenu(true)

    -- set category
    set_category("package")

    -- set description
    set_description("The libgo package")

    -- add defines to config.h if checking ok
    add_defines_h_if_ok("$(prefix)_PACKAGE_HAVE_LIBGO")

    -- add links for checking
    add_links("go", "boost_context")

    -- set languages
    set_languages("cxx11")

    -- add link directories
    add_linkdirs("lib/$(plat)/$(arch)")

    -- add c++ includes for checking
    add_cxxincludes("libgo/libgo.h", "boost/coroutine/coroutine.hpp")

    -- add include directories
    add_includedirs("inc/$(plat)", "inc")


