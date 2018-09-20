-- project
set_project("benchbox")

-- version
set_version("1.0.1")

-- set warning all as error
set_warnings("all")

-- set language: c99, c++11
set_languages("c99", "cxx11")

-- add rules: debug/release
add_rules("mode.debug", "mode.release")

-- for the windows platform (msvc)
if is_plat("windows") then 

    -- link libcmt.lib
    add_cxflags("-MT") 

    -- no msvcrt.lib
    add_ldflags("-nodefaultlib:\"msvcrt.lib\"")
end

-- the base package
option("base")
    set_default(true)
    if is_os("windows") then add_links("ws2_32") 
    elseif is_os("android") then add_links("m", "c") 
    else add_links("pthread", "dl", "m", "c") end
option_end()

-- add requires
add_requires("tbox", {config = {coroutine = true}})

-- add repositories
add_repositories("benchbox-repo repo")

-- include sources
includes("src")
