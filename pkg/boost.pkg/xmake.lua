-- add boost package
option("boost")

    -- show menu
    set_showmenu(true)

    -- set category
    set_category("package")

    -- set description
    set_description("The boost package")

    -- add defines to config.h if checking ok
    add_defines_h("$(prefix)_PACKAGE_HAVE_BOOST")

    -- add links
    if is_plat("macosx") then
        add_links("boost_coroutine", "boost_context-mt", "boost_system")
    else
        add_links("boost_coroutine", "boost_context", "boost_system")
    end

    -- add c++ includes for checking
    add_cxxincludes("boost/coroutine/coroutine.hpp")


