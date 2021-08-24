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
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/Resources/shaders/**.frag",
        "%{prj.name}/src/Resources/shaders/**.vert",
        "%{prj.name}/src/Resources/shaders/**.geom",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/Resources/TestTextures/**.png",
        "%{prj.name}/src/Resources/TestTextures/**.jpg",
        "Libraries/include/imgui/imgui_impl_glfw.cpp",
        "Libraries/include/imgui/imgui_draw.cpp",
        "Libraries/include/imgui/imgui.cpp",
        "Libraries/include/imgui/imgui_tables.cpp",
        "Libraries/include/imgui/imgui_widgets.cpp",
        "Libraries/include/imgui/imgui_demo.cpp"
    }

    includedirs 
    {
        "Libraries/include"
    }

    libdirs
    {
        "Libraries/lib"
    }

    links 
    {
        "glfw3",
        "opengl32"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "Z_PLAT_WIN",
            "Z_BUILD_DLL"
        }

        postbuildcommands 
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/ZyliphTestApp)")
        }

    filter "configurations:Debug"
        defines "Z_DEBUG"
        buildoptions "/MDd"
        symbols "On"
    
    filter "configurations:Release"
        defines "Z_RELEASE"
        buildoptions "/MD"
        optimize "On"
    
    filter "configurations:Dist"
        defines "Z_DIST"
        buildoptions "/MD"
        optimize "On"

project "ZyliphTestApp"
    location "ZyliphTestApp"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .."/%{prj.name}")
    objdir ("bin/int/" .. outputdir .."/%{prj.name}")

    files 
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp"
    }

    includedirs 
    {
        "Libraries/include",
        "ZyliphEngine/src"
    }

    links 
    {
        "ZyliphEngine"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "Z_PLAT_WIN"
        }

    filter "configurations:Debug"
        defines "Z_DEBUG"
        buildoptions "/MDd"
        symbols "On"
    
    filter "configurations:Release"
        defines "Z_RELEASE"
        buildoptions "/MD"
        optimize "On"
    
    filter "configurations:Dist"
        defines "Z_DIST"
        buildoptions "/MD"
        optimize "On"