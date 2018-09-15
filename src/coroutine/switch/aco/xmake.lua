-- enable aco?
if has_config("aco") then

    -- add target
    target("coroutine_switch_aco")

        -- set kind
        set_kind("binary")

        -- add files
        add_files("*.c")

        -- add package
        add_packages("aco", "tbox", "base")
end
