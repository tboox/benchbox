-- enable protothreads?
if is_option("protothreads") then

    -- add target
    target("coroutine_switch_protothreads")

        -- set kind
        set_kind("binary")

        -- add files
        add_files("*.c")

        -- add package
        add_packages("protothreads", "tbox", "base")
end
