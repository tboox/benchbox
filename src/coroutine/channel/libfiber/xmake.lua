-- add requires
add_requires("libfiber", {optional = true})

-- add target
target("coroutine_channel_libfiber")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("*.c")

    -- add package
    add_packages("libfiber", "tbox", "base")

    -- enable to build this target?
    before_build(function (target)
        target:set("enabled", has_config("libfiber") and true or false)
    end)
