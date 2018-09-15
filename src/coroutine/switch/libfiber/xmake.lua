-- enable libfiber?
if has_config("libfiber") then

    -- add target
    target("coroutine_switch_libfiber")

        -- set kind
        set_kind("binary")

        -- add files
        add_files("*.c")

        -- add package
        add_packages("libfiber", "tbox", "base")
end
