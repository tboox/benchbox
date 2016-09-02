-- enable cloudwu_coroutine?
if is_option("cloudwu_coroutine") then

    -- add target
    target("coroutine_switch_cloudwu")

        -- set kind
        set_kind("binary")

        -- add files
        add_files("*.c")

        -- add package
        add_packages("cloudwu_coroutine", "tbox")
end
