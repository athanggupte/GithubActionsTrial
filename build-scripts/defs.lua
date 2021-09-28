function Project(name)
    project(name)
        location(name)
        language "C++"
        cppdialect "C++17"

        files {
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/src/**.h",
        }
end

function TestProject(name)
    project("Test"..name)
        location(name.."/Test")
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"

        files {
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/src/**.h",
        }

        links {
            name,
            "gtest_main",
        }
end

function TestProjectCustomStart(name)
    project("Test"..name)
        location(name.."/Test")
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"

        files {
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/src/**.h",
        }

        links {
            name,
            "gtest",
        }
end
