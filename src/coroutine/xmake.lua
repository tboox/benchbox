-- add task
task("coroutine")

    -- on run
    on_run(function ()
 
        -- imports
        import("core.base.option")
        import("core.project.task")

        -- get testing name
        local testname = option.get("testname")
        assert(testname, "no given testing name, please run `$xmake coroutine --help` for getting more info.")

        -- walk all modules
        for _, module in ipairs(os.match("src/coroutine/*", true)) do

            -- get module name
            module = path.basename(module)

            -- run the target task
            task.run("run", {target = "coroutine_" .. module .. "_" .. testname}, option.get("arguments"))
        end
    end)

    -- set menu
    set_menu({
                    -- usage
                    usage = "xmake coroutine testname [options]"

                    -- description
                ,   description = "The coroutine benchmark."

                    -- options
                ,   options = 
                    {
                        {'n', "testname",   "kv", nil,      "The testing name."         }      
                    ,   {nil, "arguments",  "vs", nil,      "The script arguments."     }
                    }
                }) 
