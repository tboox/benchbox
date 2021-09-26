-- add tasks
for _, taskpath in ipairs(os.dirs("*")) do

    -- add task
    local taskname = path.basename(taskpath)
    task(taskname)

        -- on run
        on_run(function ()

            -- imports
            import("core.base.option")
            import("core.base.task")
            import("core.project.config")
            import("core.project.project")

            -- get case name
            local casename = option.get("casename")
            assert(casename, "no given testing name, please run `$xmake " .. taskname .. " --help` for getting more info.")

            -- load config
            config.load()

            -- walk all tests
            for _, testpath in ipairs(os.dirs(path.join(os.scriptdir(), taskname, casename, "*"))) do

                -- the target name
                local testname = path.basename(testpath)
                local targetname = taskname .. "_" .. casename .. "_" .. testname

                -- run the target task
                task.run("run", {target = targetname, arguments = option.get("arguments")})
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
                            {'n', "casename",   "kv", nil,      "The case name."

                                                                -- show all cases
                                                              , function ()

                                                                    -- imports
                                                                    import("core.project.project")

                                                                    -- make description
                                                                    local description = {}
                                                                    for i, casepath in ipairs(os.dirs(format("%s/src/%s/*", project.directory(), taskname))) do
                                                                        local casename = path.basename(casepath)
                                                                        description[i] = "    - " .. casename
                                                                    end

                                                                    -- get it
                                                                    return description
                                                                end                         }
                        ,   {}
                        ,   {nil, "arguments",  "vs", nil,      "The script arguments."     }
                        }
                    })
end

-- add tests
includes("**/xmake.lua")
