-- enable coroutine?
if is_option("coroutine") then

    -- add target
    target("coroutine_switch_coroutine")

        -- set kind
        set_kind("binary")

        -- add files
        add_files("*.c")

        -- add package
        add_packages("coroutine", "tbox", "base")
end
