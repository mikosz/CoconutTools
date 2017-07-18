include "premake5.cfg.lua"

newoption {
   trigger     = "shared-libs",
   description = "Build shared instead of static libraries"
}

function source_dir(kind)
	return "src/" .. kind .. "/c++/"
end
	
function source_patterns(kind)
	return { source_dir(kind) .. "**.hpp", source_dir(kind) .. "**.cpp" }
end

function create_vpaths(patterns, kind)
	for _, pattern in pairs(patterns) do
		for _, file in pairs(os.matchfiles(pattern)) do
			local file_with_namespace = file:sub(string.len(source_dir(kind)) + 1)
			local namespace_path = path.getdirectory(file_with_namespace)
			vpaths { [ namespace_path:gsub("/", "::") ] = file }
		end
	end
end

function sources(kind)
	local patterns = source_patterns(kind)
	create_vpaths(patterns, kind)
	files(patterns)
end
	
function test_projects(name, is_library, common_settings)
	if not table.isempty(os.matchfiles(source_dir("test") .. "**.cpp")) then
		project(name .. "-unit-test")
			kind "ConsoleApp"
			sources("test")
			includedirs { source_dir("main") }
			if is_library then
				links(name)
			end
			if common_settings then
				common_settings()
			end
	end

	if not table.isempty(os.matchfiles(source_dir("functional-test") .. "**.cpp")) then
		project(name .. "-functional-test")
			kind "ConsoleApp"
			sources("functional-test")
			includedirs { source_dir("main") }
			if is_library then
				links(name)
			end
			if common_settings then
				common_settings()
			end
	end
	
	project "*"
end

function header_project(name)
	project(name)
		kind "Utility"
		sources("main")

	test_projects(name, false)
end

function library_project(name, common_settings)
	project(name)
		configuration "shared-libs"
			kind "SharedLib"

		configuration "not shared-libs"
			kind "StaticLib"
			
		configuration {}
			
		sources("main")
		
		if common_settings then
			common_settings()
		end
		
	test_projects(name, true, common_settings)
end

function link_boost_libs(names)
	for _, name in pairs(names) do
		name = "boost_" .. name

		local prefix = ""
		if BOOST_USE_STATIC_LIBS then
			prefix = "lib"
		end
		
		local mt_part = ""
		if BOOST_MULTITHREADED then
			mt_part = "-mt"
		end
		
		local toolset_part = ""
		if BOOST_TOOLSET then
			toolset_part = "-" .. BOOST_TOOLSET
		end

		local version_part = ""
		if BOOST_VERSION then
			version_part = "-" .. BOOST_VERSION
		end
		
		filter "configurations:Debug*"
			links(prefix .. name .. toolset_part .. mt_part .. "-gd" .. version_part)
		filter "configurations:Release*"
			links(prefix .. name .. toolset_part .. mt_part .. version_part)
		filter {}
	end
end

function add_gmock_files()
	includedirs(GMOCK_DIR)
	includedirs(GMOCK_DIR .. "/include/")
	includedirs(GMOCK_DIR .. "/gtest/")
	includedirs(GMOCK_DIR .. "/gtest/include/")

	local gmock_all_file = GMOCK_DIR .. "/src/gmock-all.cc"
	local gtest_all_file = GMOCK_DIR .. "/gtest/src/gtest-all.cc"
	files { gmock_all_file, gtest_all_file }
	vpaths { [ ".external" ] = { gmock_all_file, gtest_all_file } }
end

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
