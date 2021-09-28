workspace "GithubActionsTrial"
    architecture "x64"
    configurations {
        "Debug",
        "Release"
    }

include "build-scripts/defs.lua"
include "build-scripts/deps.lua"

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
