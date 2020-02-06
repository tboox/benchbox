-- add requires
add_requires("libaco", {optional = true})

-- add target
target("coroutine_switch_libaco")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("*.c")

    -- add package
    add_packages("libaco", "tbox")

    -- enable to build this target?
    on_load(function (target)
        target:set("enabled", has_package("libaco") and true or false)
    end)
