workspace "ZyliphEngine"
    architecture "x64"

    configurations 
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "ZyliphEngine"
    location "ZyliphEngine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .."/%{prj.name}")
    objdir ("bin/int/" .. outputdir .."/%{prj.name}")

    files 
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/Resources/shaders/**.frag",
        "%{prj.name}/src/Resources/shaders/**.vert",
        "%{prj.name}/src/Resources/shaders/**.geom",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/Resources/TestTextures/**.png",
        "%{prj.name}/src/Resources/TestTextures/**.jpg"
    }