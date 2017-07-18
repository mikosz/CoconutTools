function factory_common()
	links { "coconut-tools-exceptions" }
end

library_project("coconut-tools-factory", factory_common)

project "coconut-tools-factory-unit-test"
	add_gmock_files()
	