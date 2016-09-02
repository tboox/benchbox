-- add target
target("other_case1_test2")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("*.c")

    -- add package
    add_packages("tbox", "base")

