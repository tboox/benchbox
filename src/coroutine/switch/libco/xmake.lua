-- add requires
add_requires("libco", {optional = true})

-- add target
target("coroutine_switch_libco")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("*.cpp")

    -- add package
    add_packages("libco", "tbox")

    -- enable to build this target?
    on_load(function (target)
        target:set("enabled", has_package("libco") and true or false)
    end)
