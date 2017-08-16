include "premake5.cfg.lua"

structure = require "structure"

include "boost.lua"
include "gmock.lua"

workspace "CoconutTools"

	-- configurations { "DebugStatic", "DebugShared", "ReleaseStatic", "ReleaseShared" }
	configurations { "DebugStatic", "ReleaseStatic" } -- dllexport not set up
	
	platforms { "Win64" }
	
	language "C++"

	location "build"
	
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

	structure.create_install_project()
	structure.create_run_tests_project()
	