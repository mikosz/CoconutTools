function logger_common()
	links { "coconut-tools-configuration", "coconut-tools-system" }
end

library_project("coconut-tools-logger", logger_common)

project "coconut-tools-logger-unit-test"
	add_gmock_files()
	