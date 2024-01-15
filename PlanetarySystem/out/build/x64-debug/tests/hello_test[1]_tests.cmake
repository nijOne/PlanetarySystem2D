add_test([=[HelloTest.BasicAssertions]=]  C:/Users/Jakub/source/repos/PlanetarySystem/PlanetarySystem/out/build/x64-debug/tests/hello_test.exe [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HelloTest.BasicAssertions]=]  PROPERTIES WORKING_DIRECTORY C:/Users/Jakub/source/repos/PlanetarySystem/PlanetarySystem/out/build/x64-debug/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  hello_test_TESTS HelloTest.BasicAssertions)
