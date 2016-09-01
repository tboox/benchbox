-- add tasks
for _, taskname in ipairs(os.dirs("*"), path.basename) do

    -- add task
    task(taskname)

        -- on run
        on_run(function ()
     
            -- imports
            import("core.base.option")
            import("core.project.task")

            -- get case name
            local casename = option.get("casename")
            assert(casename, "no given testing name, please run `$xmake " .. taskname .. " --help` for getting more info.")

            -- walk all tests
            for _, testname in ipairs(os.dirs(path.join(path.join(os.scriptdir(), taskname), "*")), path.basename) do

                -- run the target task
                task.run("run", {target = taskname .. "_" .. testname .. "_" .. casename, arguments = option.get("arguments")})
            end
        end)

        -- set menu
        set_menu({
                        -- usage
                        usage = "xmake " .. taskname .. " casename [options]"

                        -- description
                    ,   description = "The " .. taskname .. " benchmark."

                        -- options
                    ,   options = 
                        {
                            {'n', "casename",   "kv", nil,      "The testing name."         }      
                        ,   {}
                        ,   {nil, "arguments",  "vs", nil,      "The script arguments."     }
                        }
                    }) 
end

-- add tests
add_subfiles("**/xmake.lua")
