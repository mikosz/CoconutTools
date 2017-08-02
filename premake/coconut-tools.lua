function link_coconut_tools_libs(names)
	for _, name in pairs(names) do
		name = "coconut-tools-"..name

		local prefix = ""
		if COCONUT_TOOLS_USE_STATIC_LIBS then
			prefix = "lib"
		end
		
		filter "configurations:Debug*"
			links(prefix..name..".d")
		filter "configurations:Release*"
			links(prefix..name)
		filter {}
	end
end
