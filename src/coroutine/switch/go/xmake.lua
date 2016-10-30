-- add target
target("coroutine_switch_go")

    -- set kind
    set_kind("binary")

    -- not build
    on_build(function() end)

    -- run it
    on_run(function ()
 
        -- imports
        import("core.base.option")

        -- run go
        try
        {
            function ()

                -- get arguments
                local args = ""
                if option.get("arguments") then
                    args = table.concat(option.get("arguments"), " ")
                end

                -- run it
                os.exec("go run %s %s", path.join(os.scriptdir(), "main.go"), args)
            end
        }
    end)
