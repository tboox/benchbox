-- add requires
add_requires("libmill", {optional = true})

-- enable libmill?
if has_config("libmill") then

    -- add target
    target("coroutine_channel_libmill")

        -- set kind
        set_kind("binary")

        -- add files
        add_files("*.c")

        -- add package
        add_packages("libmill", "tbox", "base")
end
