for _, casename in ipairs(os.files("*.c"), path.basename) do

    -- add target
    target("other_test2_" .. casename)

        -- set kind
        set_kind("binary")

        -- add files
        add_files(casename .. ".c")

        -- add package
        add_packages("tbox")

end
