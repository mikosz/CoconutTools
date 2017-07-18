library_project "coconut-tools-configuration"

project "coconut-tools-configuration-unit-test"
	add_gmock_files()
	links { "coconut-tools-exceptions", "coconut-tools-system" }
