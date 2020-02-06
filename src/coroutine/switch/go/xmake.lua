-- add requires
add_requires("go", {optional = true})

-- add target
target("coroutine_switch_go")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("*.go")

    -- add packages
    add_packages("go")

    -- enable to build this target?
    on_load(function (target)
        target:set("enabled", has_package("go") and true or false)
    end)
