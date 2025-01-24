# This is like declaring what type of meal you’re making and the tools (CMake version) you’ll need.
cmake_minimum_required(VERSION 3.28)
project(tutorial)

# with this option cmake generates a JSON files
# containing compile info like include paths
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)







# how to get the external dependencies/like grpc, protobuff
# it should be the cmake project and should should be somewhere in the system

find_package(Eigen3 REQUIRED)

# or add the libraries (you own codes) or use external ones
# making the library of the sum library(say it is the complex math library)
add_library(sum lib/sum.cc)
# Use target_include_directories() for header file paths
# This function is meant for specifying additional library search paths, not for linking header files.
target_include_directories(sum PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)









# specifies which files will be compiled into executables or libraries
# You’re listing the main ingredients (source files) for your recipe.
add_executable(hello src/hello.cc) # Creates a target (the final executable) from your source files







# Links a library to an executable or another library.
target_link_libraries(hello sum Eigen3::Eigen) # Libraries are like reusable components (pre-made sauces or mixes) you add to your recipe.

# how to add external projects 






# the keyword PUBLIC, PRIVATE, INTERFACE
# define the how dependencies and include directories are propagated between targets

# PRIVATE:
    # Only used within the current target's implementation
    # Not shared with targets that link to this target
    # Dependency is hidden from downstream consumers2

# PUBLIC:
    # Used both within the current target's implementation
    # Also shared with targets that link to this target
    # Affects both the current target and its consumers2

# INTERFACE:
    # Only used by targets that consume this target
    # Not used in the current target's implementation
    # Primarily for header-only libraries or dependencies only needed by consumers

# Specific to target_include_directories()
# For the specific example target_include_directories(sum PUBLIC include/sum.hh):
#     The include/sum.hh directory will be:
#         Used when compiling the sum target
#         Automatically made availab le to any target that links to sum

# Pro Tip: Choose the keyword based on how the headers or dependencies will be used across your project's targets. PUBLIC should be used sparingly and only when truly necessary


# installation and export

# who gonna use the library going to have the header file
install(
    DIRECTORY include/
    DESTINATION include
)

# explicitly tell which targets we want to export
# in this case we have the sum as sum-targets
install(TARGETS sum
    EXPORT sum-targets
    ARCHIVE DESTINATION lib
    # ARCHIVE: types of the artifact we're exporting
)

install(EXPORT sum-targets
    NAMESPACE something::
    DESTINATION lib/cmake/sum
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/sum-config.cmake.in sum-config.cmake
                COPYONLY)

install(FILES
    ${CMAKE_BINARY_DIR}/sum-config.cmake
    DESTINATION lib/cmake/sum
)
