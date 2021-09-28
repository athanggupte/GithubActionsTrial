--[[
    The Google test project without main function.
    To be used for tests which require a custom main function
--]]
project "gtest"
    location "../dependencies/googletest"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    files {
        "%{prj.location}/googletest/include/**.h",
        -- "%{prj.location}/googlemock/include/**.h",
        "%{prj.location}/googletest/src/gtest-all.cc",
    }

    includedirs {
        "%{prj.location}/googletest/include"
    }

--[[
    The Google test project with simple predefined main function.
    Prefered for most tests
--]]
project "gtest_main"
    location "../dependencies/googletest"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    files {
        "%{prj.location}/googletest/include/**.h",
        -- "%{prj.location}/googlemock/**.h",
        "%{prj.location}/googletest/src/gtest-main.cc",
    }

    includedirs {
        "%{prj.location}/googletest/include"
    }

    links {
        "gtest"
    }