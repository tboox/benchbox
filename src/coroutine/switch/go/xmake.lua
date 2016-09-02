-- add target
target("coroutine_switch_go")

    -- set kind
    set_kind("binary")

    -- add files
    add_files("*.c")

    -- run it
    on_run(function ()

        -- run go
        try
        {
            function ()
                os.exec("go run %s", path.join(os.scriptdir(), "main.go"))
            end
        }
    end)
