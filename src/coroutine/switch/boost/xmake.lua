-- add requires
add_requires("boost", {optional = true, configs = {coroutine = true, context = true}})

-- add target
target("coroutine_switch_boost")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("*.cpp")

    -- add package
    add_packages("boost", "tbox")

    -- enable to build this target?
    on_load(function (target)
        target:set("enabled", has_package("boost") and true or false)
    end)
