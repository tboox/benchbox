-- add requires
add_requires("libmill", {optional = true})

-- add target
target("coroutine_switch_libmill")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("*.c")

    -- add package
    add_packages("libmill", "tbox")

    -- enable to build this target?
    on_load(function (target)
        target:set("enabled", has_package("libmill") and true or false)
    end)
