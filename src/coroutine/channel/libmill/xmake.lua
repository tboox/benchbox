-- enable libmill?
if is_option("libmill") then

    -- add target
    target("coroutine_channel_libmill")

        -- set kind
        set_kind("binary")

        -- add files
        add_files("*.c")

        -- add package
        add_packages("libmill", "tbox", "base")
end
