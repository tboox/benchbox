-- enable libgo?
if is_option("libgo") then

    -- add target
    target("coroutine_channel_libgo")

        -- set kind
        set_kind("binary")

        -- add files
        add_files("*.cpp")

        -- add package
        add_packages("libgo", "tbox", "base")
end
