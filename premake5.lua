include "premake5.cfg.lua"

include "premake/project.lua"
include "premake/boost.lua"
include "premake/gmock.lua"

workspace "CoconutTools"

	configurations { "DebugStatic", "DebugShared", "ReleaseStatic", "ReleaseShared" }
	
	platforms { "Win64" }
	
	language "C++"

	location "build"
	targetdir("%{wks.location}/bin/%{prj.name}/%{cfg.platform}/%{cfg.shortname}")
	objdir("%{wks.location}/obj/%{prj.name}/%{cfg.platform}/%{cfg.shortname}")
		
	-- Configuration specific settings
	
	filter "configurations:Debug*"
		symbols "On"
		
	filter "configurations:Release*"
		defines { "NDEBUG" }
		optimize "On"
	
	-- Platform specific settings
	
	filter "platforms:Win32"
		system "Windows"
		architecture "x32"

	filter "platforms:Win64"
		system "Windows"
		architecture "x64"
		
	filter {}
	
	-- Global includes
	
	includedirs { "*/" .. source_dir("main") }
	includedirs { BOOST_INCLUDE_DIR }
	
	-- Dependency libraries
	
	libdirs { BOOST_LIB_DIR }
	
	-- Warnings
	
	warnings "Extra"
	flags { "FatalWarnings" }
	
	filter "action:vs*"
		defines { "_SCL_SECURE_NO_WARNINGS" }
	filter {}
	
include "coconut-tools-bits"
include "coconut-tools-concurrent"
include "coconut-tools-configuration"
include "coconut-tools-enums"
include "coconut-tools-exceptions"
include "coconut-tools-factory"
include "coconut-tools-logger"
include "coconut-tools-policy"
include "coconut-tools-serialisation"
include "coconut-tools-singleton"
include "coconut-tools-system"
include "coconut-tools-test-utils"
include "coconut-tools-utils"
include "coconut-tools-version"
