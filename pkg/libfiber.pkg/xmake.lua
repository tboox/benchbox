-- add libfiber package
option("libfiber")

    -- show menu
    set_showmenu(true)

    -- set category
    set_category("package")

    -- set description
    set_description("The libfiber package")

    -- add defines to config.h if checking ok
    add_defines_h_if_ok("$(prefix)_PACKAGE_HAVE_LIBFIBER")

    -- add links for checking
    add_links("fiber", "acl")

    -- add link directories
    add_linkdirs("lib/$(plat)/$(arch)", "/usr/local/lib/linux64")

    -- add c includes for checking
    add_cincludes("acl/lib_fiber.h")

    -- add include directories
    add_includedirs("inc/$(plat)", "inc")

