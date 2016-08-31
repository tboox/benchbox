-- add libtask package
option("libtask")

    -- show menu
    set_showmenu(true)

    -- set category
    set_category("package")

    -- set description
    set_description("The libtask package")

    -- add defines to config.h if checking ok
    add_defines_h_if_ok("$(prefix)_PACKAGE_HAVE_LIBTASK")

    -- add links for checking
    add_links("task")

    -- add link directories
    add_linkdirs("lib/$(plat)/$(arch)")

    -- add c includes for checking
    add_cincludes("task/task.h")

    -- add include directories
    add_includedirs("inc/$(plat)", "inc")


