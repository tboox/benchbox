-- add requires
add_requires("libtask", {optional = true})

-- add target
target("coroutine_channel_libtask")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("*.c")

    -- add package
    add_packages("libtask", "tbox", "base")

    -- enable to build this target?
    before_build(function (target)
        target:set("enabled", has_package("libtask") and true or false)
    end)
