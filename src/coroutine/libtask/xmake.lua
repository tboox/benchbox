-- enable libtask?
if is_option("libtask") then

    -- add target
    target("coroutine_libtask_switch")

        -- set kind
        set_kind("binary")

        -- add files
        add_files("*.c")

        -- add package
        add_packages("libtask", "tbox")
end
