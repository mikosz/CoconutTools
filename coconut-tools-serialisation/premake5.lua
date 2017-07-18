function serialisation_common()
	links { "coconut-tools-configuration", "coconut-tools-system" }
end

library_project("coconut-tools-serialisation", serialisation_common)

project "coconut-tools-serialisation-unit-test"
	add_gmock_files()
	