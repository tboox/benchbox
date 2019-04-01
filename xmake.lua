-- project
set_project("benchbox")

-- version
set_version("1.0.1")
set_xmakever("2.2.5")

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

-- add syslinks
if is_plat("windows") then
    add_syslinks("ws2_32") 
elseif is_plat("android") then
    add_syslinks("m", "c") 
elseif is_plat("mingw") then
    add_syslinks("ws2_32", "pthread", "m")
else 
    add_syslinks("pthread", "dl", "m", "c") 
end

-- add requires
add_requires("tbox", {configs = {coroutine = true}})

-- add repositories
add_repositories("benchbox-repo repo")

-- include sources
includes("src")
