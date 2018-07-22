-- add libmill package
option("libmill")

    -- show menu
    set_showmenu(true)

    -- set category
    set_category("package")

    -- set description
    set_description("The libmill package")

    -- add defines to config.h if checking ok
    add_defines_h("$(prefix)_PACKAGE_HAVE_LIBMILL")

    -- add links for checking
    add_links("mill")

    -- add link directories
    add_linkdirs("lib/$(plat)/$(arch)")

    -- add c includes for checking
    add_cincludes("libmill.h")

    -- add include directories
    add_includedirs("inc/$(plat)", "inc")


