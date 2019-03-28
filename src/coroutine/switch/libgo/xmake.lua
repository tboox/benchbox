-- add requires
add_requires("libgo", {optional = true})

-- add target
target("coroutine_switch_libgo")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("*.cpp")

    -- add package
    add_packages("libgo", "tbox")

    -- enable to build this target?
    before_build(function (target)
        target:set("enabled", has_package("libgo") and true or false)
    end)
