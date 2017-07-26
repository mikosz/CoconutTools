function system_common()
	link_boost_libs { "filesystem" }
	links { "coconut-tools-exceptions" }
end

structure.library_project("coconut-tools-system", system_common)
