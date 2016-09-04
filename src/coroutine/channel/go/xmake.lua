-- add target
target("coroutine_channel_go")

    -- set kind
    set_kind("binary")

    -- not build
    on_build(function() end)

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
