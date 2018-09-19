-- add requires
add_requires("go", {optional = true})

-- add target
target("coroutine_switch_go")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("*.go")

    -- enable to build this target?
    before_build(function (target)
        target:set("enabled", has_config("go") and true or false)
    end)
