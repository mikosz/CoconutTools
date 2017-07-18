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
