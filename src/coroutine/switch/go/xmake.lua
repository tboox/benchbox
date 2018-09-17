-- add requires
add_requires("go", {optional = true})

-- enable go?
if has_config("go") then

    -- add target
    target("coroutine_switch_go")

        -- set kind
        set_kind("binary")

        -- add files
        add_files("*.go")
end
