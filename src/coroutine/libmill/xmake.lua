-- enable libmill?
--if is_option("libmill") then

    -- add target
    target("coroutine_libmill_switch")

        -- set kind
        set_kind("binary")

        -- add files
        add_files("*.c")

        -- add package
        add_packages("libmill", "tbox")
--end
