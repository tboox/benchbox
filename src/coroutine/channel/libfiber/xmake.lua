-- enable libfiber?
if is_option("libfiber") then

    -- add target
    target("coroutine_channel_libfiber")

        -- set kind
        set_kind("binary")

        -- add files
        add_files("*.c")

        -- add package
        add_packages("libfiber", "tbox", "base")
end
