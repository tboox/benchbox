-- add requires
add_requires("libfiber", {optional = true})

-- add target
target("coroutine_switch_libfiber")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("*.c")

    -- add package
    add_packages("libfiber", "tbox")

    -- add links
    if is_plat("windows") then
        add_links("kernel32", "user32", "gdi32", "winspool", "comdlg32", "advapi32", "ws2_32")
    end

    -- enable to build this target?
    before_build(function (target)
        target:set("enabled", has_package("libfiber") and true or false)
    end)
