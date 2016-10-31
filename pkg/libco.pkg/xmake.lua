-- add libco package
option("libco")

    -- show menu
    set_showmenu(true)

    -- set category
    set_category("package")

    -- set description
    set_description("The libco package")

    -- add defines to config.h if checking ok
    add_defines_h_if_ok("$(prefix)_PACKAGE_HAVE_LIBCO")

    -- add links for checking
    add_links("colib")

    -- add link directories
    add_linkdirs("lib/$(plat)/$(arch)")

    -- add c includes for checking
    add_cxxincludes("co_routine.h")

    -- add include directories
    add_includedirs("inc/$(plat)", "inc")


