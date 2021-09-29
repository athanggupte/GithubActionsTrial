workspace "GithubActionsTrial"
    architecture "x64"
    configurations {
        "Debug",
        "Release"
    }

include "build-scripts/defs.lua"
include "build-scripts/deps.lua"

-- Library
Project "SomeLib"
    kind "StaticLib"

TestProject "SomeLib"

-- Main executable project
Project "SomeApp"
    kind "ConsoleApp"

    links {
        "SomeLib"
    }

TestProject "SomeApp"

-- ======================================
--           Custom actions
-- ======================================
newaction {
    trigger     = "clean",
    description = "Clean all build and output files the workspace",
    execute = function ()

        files_to_del = {
            -- gmake
            "Makefile",
            "*.make",
            -- Visual Studio
            "*.sln",
            "*.vcxproj",
            "*.vcxproj.user",
            "*.vcxproj.filters",
            -- xcode
        }

        dirs_to_del = {
            -- Outputs
            "bin",
            "obj",
            "docs",
            -- vscode
            ".vs",
        }

        for i,v in ipairs(dirs_to_del) do
            os.rmdir(_MAIN_SCRIPT_DIR.."/"..v)
        end

        if os.istarget "linux" then
            for i,v in ipairs(files_to_del) do
                os.chdir(_MAIN_SCRIPT_DIR)
                os.execute("rm -f \""..v.."\"")
                os.chdir(_WORKING_DIR)
            end
        elseif os.istarget "windows" then
            for i,v in ipairs(files_to_del) do
                os.chdir(_MAIN_SCRIPT_DIR)
                os.execute("del /f/s/q \""..v.."\"")
                os.chdir(_WORKING_DIR)
            end
        end

    end
}