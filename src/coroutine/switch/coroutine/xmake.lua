-- add requires
add_requires("coroutine", {optional = true})

-- add target
target("coroutine_switch_coroutine")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("*.c")

    -- add package
    add_packages("coroutine", "tbox", "base")

    -- enable to build this target?
    before_build(function (target)
        target:set("enabled", has_config("coroutine") and true or false)
    end)
