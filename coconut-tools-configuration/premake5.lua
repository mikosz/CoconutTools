function configuration_common()
	links { "coconut-tools-exceptions", "coconut-tools-system" }
end

structure.library_project("coconut-tools-configuration", configuration_common)

project "coconut-tools-configuration-unit-test"
	add_gmock_files()
