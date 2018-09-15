-- enable libgo?
if has_config("libgo") then

    -- add target
    target("coroutine_switch_libgo")

        -- set kind
        set_kind("binary")

        -- add files
        add_files("*.cpp")

        -- add package
        add_packages("libgo", "tbox", "base")
end
