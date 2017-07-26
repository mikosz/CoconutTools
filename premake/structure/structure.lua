local m = {}

local headers = {}
local library_projects = {}
local test_projects = {}

-- directories

objdir("%{wks.location}/obj/%{prj.name}/%{cfg.shortname}")

local target_dir_path = function(parent)
	return "%{wks.location}/%{cfg.shortname}/"..parent.."/"
end

-- header_project and library_project

local source_dir = function(kind)
	return "src/"..kind.."/c++/"
end

local source_patterns = function(kind)
	return { source_dir(kind).."**.hpp", source_dir(kind).."**.cpp" }
end

local create_vpaths = function(patterns, kind)
	for _, pattern in pairs(patterns) do
		for _, file in pairs(os.matchfiles(pattern)) do
			local file_with_namespace = file:sub(string.len(source_dir(kind)) + 1)
			local namespace_path = path.getdirectory(file_with_namespace)
			vpaths { [ namespace_path:gsub("/", "::") ] = file }
		end
	end
end

local sources = function(kind)
	local patterns = source_patterns(kind)
	create_vpaths(patterns, kind)
	files(patterns)
end

local create_test_projects = function(name, is_library, common_settings)
	if not table.isempty(os.matchfiles(source_dir("test").."**.cpp")) then
		project(name.."-unit-test")
			kind "ConsoleApp"
			targetdir(target_dir_path("tests"))
			sources("test")
			includedirs { source_dir("main") }
			if is_library then
				links(name)
			end
			if common_settings then
				common_settings()
			end
		project "*"
		
		table.insert(test_projects, name.."-unit-test")
	end

	if not table.isempty(os.matchfiles(source_dir("functional-test").."**.cpp")) then
		project(name.."-functional-test")
			kind "ConsoleApp"
			targetdir(target_dir_path("tests"))
			sources("functional-test")
			includedirs { source_dir("main") }
			if is_library then
				links(name)
			end
			if common_settings then
				common_settings()
			end

			table.insert(test_projects, name.."-functional-test")
		project "*"
	end
end

local gather_headers = function()
	for _, file in pairs(os.matchfiles(source_dir("main").."**.hpp")) do
		local source = path.getabsolute(file)
		local target = file:gsub("src/main/c%+%+/", "")
		headers[source] = target
	end
end

local create_project = function(name)
	project(name)
		sources "main"
	project "*"
		includedirs(source_dir("main"))
		
	gather_headers()
end

function m.header_project(name)
	create_project(name)

	project(name)
		kind "Utility"
	project "*"
	
	create_test_projects(name, false)
end

function m.library_project(name, common_settings)
	create_project(name)

	project(name)
		filter "configurations:*Shared"
			kind "SharedLib"
		filter "configurations:*Static"
			kind "StaticLib"
			targetprefix("lib")
		filter {}
		
		targetdir(target_dir_path("lib"))
		
		filter "configurations:Debug*"
			targetsuffix(".d")
		filter {}
		
		if common_settings then
			common_settings()
		end
	project "*"
	
	table.insert(library_projects, name)

	create_test_projects(name, true, common_settings)
end

-- install target

newoption {
   trigger = "install-prefix",
   value = "path",
   description = "Directory the install action will copy files into"
}
local install_prefix = _OPTIONS["install-prefix"]

function m.create_install_project()
	project "INSTALL"
		kind "Utility"
		dependson(library_projects)
		
		if not install_prefix then
			premake.error("install-prefix not specified")
		end

		local lib_directory = path.join(install_prefix, "lib")
		
		for _, library in pairs(library_projects) do
			postbuildcommands {
				"{ECHO} installing "..library
			}
		
			filter "configurations:DebugStatic"
				postbuildcommands {
					"{COPY} %{wks.location}%{cfg.shortname}/lib/lib"..library..".d.lib "..lib_directory
				}
			filter "configurations:DebugShared"
				postbuildcommands {
					"{COPY} %{wks.location}%{cfg.shortname}/lib/"..library..".d.lib "..lib_directory,
					"{COPY} %{wks.location}%{cfg.shortname}/lib/"..library..".d.dll "..lib_directory
				}
			filter "configurations:ReleaseStatic"
				postbuildcommands {
					"{COPY} %{wks.location}%{cfg.shortname}/lib/lib"..library..".lib "..lib_directory
				}
			filter "configurations:ReleaseShared"
				postbuildcommands {
					"{COPY} %{wks.location}%{cfg.shortname}/lib/"..library..".lib "..lib_directory,
					"{COPY} %{wks.location}%{cfg.shortname}/lib/"..library..".dll "..lib_directory
				}
			filter {}
		end

		-- TODO: auto dll exports
		-- TODO: install and run_tests require rebuild to run
		-- TODO: add rmdir before installing headers
		-- TODO: mkdir only if necessary, otherwise spewing warning messages
		
		for file, target in pairs(headers) do
			local target_dir = path.getdirectory(path.join(install_prefix, "include", target))
			postbuildcommands {
				"{ECHO} installing "..file,
				"{MKDIR} "..target_dir,
				"{COPY} "..file.." "..target_dir
			}
		end
	project "*"
end

function m.create_run_tests_project()
	project "RUN_TESTS"
		kind "Utility"
		dependson(test_projects)
		
		for _, test in pairs(test_projects) do
			postbuildcommands {
				"{ECHO} Running "..test,
				"%{wks.location}%{cfg.shortname}/tests/"..test..".exe" -- ".exe" could come from a token?
			}
		end
	project "*"
end

return m
