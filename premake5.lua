workspace "GithubActionsTrial"
    architecture "x64"
    configurations {
        "Debug",
        "Release"
    }

include "scripts/defs.lua"
include "scripts/deps.lua"

newoption {
    trigger     = "build-tests",
    description = "Build unit tests or skip",
    default     = "yes",
    allowed = {
        { "yes", "Builds the unit tests" },
        { "no",  "Skips unit tests" }
    }
}

-- Library
Project "SomeLib"
    kind "StaticLib"

if _OPTIONS["build-tests"] == "yes" then
    TestProject "SomeLib"
end

-- Main executable project
Project "SomeApp"
    kind "ConsoleApp"

    includedirs {
        "SomeLib/src"
    }

    links {
        "SomeLib"
    }

if _OPTIONS["build-tests"] == "yes" then
    TestProject "SomeApp"
end

-- ======================================
--           Custom actions
-- ======================================
newaction {
    trigger     = "run-tests",
    description = "Run all unit tests",
    execute = function ()

        if os.istarget "linux" then
            os.execute "scripts/run_tests.sh"
        elseif os.istarget "windows" then
            os.execute "dir /b"
            os.execute "scripts\\run_tests.bat"
        end

    end
}

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
        }


        os.chdir(_MAIN_SCRIPT_DIR)
        for i,v in ipairs(dirs_to_del) do
            os.rmdir(v)
        end

        if os.istarget "linux" then
            for i,v in ipairs(files_to_del) do
                os.execute("find . -type f -name '"..v.."' -delete")
            end
        elseif os.istarget "windows" then
            for i,v in ipairs(files_to_del) do
                os.execute("del /f/s/q \""..v.."\"")
            end
        end
        os.chdir(_WORKING_DIR)

    end
}