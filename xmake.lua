-- project
set_project("benchbox")

-- version
set_version("1.0.1")

-- set warning all as error
set_warnings("all")

-- set language: c99, c++11
set_languages("c99", "cxx11")

-- set the symbols visibility: hidden
set_symbols("debug")

-- strip all symbols
set_strip("all")

-- fomit the frame pointer
--add_cxflags("-fomit-frame-pointer")
--add_mxflags("-fomit-frame-pointer")

-- enable fastest optimization
set_optimize("fastest")

-- attempt to add vector extensions 
add_vectorexts("sse2", "sse3", "ssse3", "mmx")

-- for the windows platform (msvc)
if is_plat("windows") then 

    -- link libcmt.lib
    add_cxflags("-MT") 

    -- no msvcrt.lib
    add_ldflags("-nodefaultlib:\"msvcrt.lib\"")
end

-- add package directories
add_packagedirs("pkg") 

-- add subprojects
add_subdirs("src")
