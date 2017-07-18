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
