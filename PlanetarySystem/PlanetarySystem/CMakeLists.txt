# CMakeList.txt : CMake project for PlanetarySystem, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (PlanetarySystem "PlanetarySystem.cpp" "PlanetarySystem.h" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PlanetarySystem PROPERTY CXX_STANDARD 17)
endif()
target_include_directories(PlanetarySystem PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(PlanetarySystem INTERFACE cxx_std_17)


# TODO: Add tests and install targets if needed.
