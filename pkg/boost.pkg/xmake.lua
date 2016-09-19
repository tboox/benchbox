-- add boost package
option("boost")

    -- show menu
    set_showmenu(true)

    -- set category
    set_category("package")

    -- set description
    set_description("The boost package")

    -- add defines to config.h if checking ok
    add_defines_h_if_ok("$(prefix)_PACKAGE_HAVE_BOOST")

    -- add links
    add_links("boost_coroutine", "boost_system")

    -- add c++ includes for checking
    add_cxxincludes("boost/asio.hpp")


