-- enable boost?
if has_config("boost") then

    -- add target
    target("coroutine_switch_boost")

        -- set kind
        set_kind("binary")

        -- add files
        add_files("*.cpp")

        -- add package
        add_packages("boost", "tbox", "base")
end
