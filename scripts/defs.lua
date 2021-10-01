outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

function Project(name)
    project(name)
        location(name)
        language "C++"
        cppdialect "C++17"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("obj/" .. outputdir .. "/%{prj.name}")

        files {
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/src/**.h",
        }

        filter "configurations:Debug"
            runtime "Debug"
            symbols "On"
            
        filter "configurations:Release"
            runtime "Release"
            optimize "On"

        filter "*"
end

function TestProject(name)
    group "Tests"
    project("Test"..name)
        location(name.."/Test")
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"

        targetdir ("bin/" .. outputdir .. "/tests/%{prj.name}")
        objdir ("obj/" .. outputdir .. "/%{prj.name}")        

        files {
            name.."/Test/src/**.cpp",
            name.."/Test/src/**.h",
        }

        includedirs {
            name.."/src",
            "dependencies/googletest/googletest/include",
        }

        links {
            name,
            "gtest_main",
        }

        filter "configurations:Debug"
            runtime "Debug"
            symbols "On"
            
        filter "configurations:Release"
            runtime "Release"
            optimize "On"

        filter "system:linux"
            links {
                "pthread",
                "gtest"
            }

        filter "*"
    group ""
end

function TestProjectCustomStart(name)
    group "Tests"
    project("Test"..name)
        location(name.."/Test")
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("obj/" .. outputdir .. "/%{prj.name}")

        files {
            name.."/Test/src/**.cpp",
            name.."/Test/src/**.h",
        }

        includedirs {
            name.."/src",
            "dependencies/googletest/googletest/include",
        }

        links {
            name,
            "gtest",
        }
        
        filter "configurations:Debug"
            runtime "Debug"
            symbols "On"
            
        filter "configurations:Release"
            runtime "Release"
            optimize "On"

        filter "system:linux"
            links {
                "pthread",
                "gtest"
            }

        filter "*"
    group ""
end
