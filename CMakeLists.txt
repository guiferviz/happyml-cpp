
cmake_minimum_required(VERSION 2.8.9)
project(happyml CXX)
set(HAPPY_ML_VERSION "1.0")
set(INCLUDE_DIR "include")
set(SOURCES_DIR "src")
set(TEST_DIR "test")
set(LIBRARY_OUTPUT_DIR "lib")

# Including header files at include dir.
include_directories(${INCLUDE_DIR})

# ALL cpp files under src.
file(GLOB SOURCES ${SOURCES_DIR}/*.cpp)

# Generate the shared library from the sources.
add_library(${PROJECT_NAME} SHARED ${SOURCES})
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${LIBRARY_OUTPUT_DIR})

# External libraries.
target_link_libraries(${PROJECT_NAME} m armadillo)

# Location for library installation.
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
install(FILES ${INCLUDE_DIR}/${PROJECT_NAME}.h DESTINATION include)
install(DIRECTORY ${INCLUDE_DIR}/${PROJECT_NAME} DESTINATION include)

# Adding definitions to use with the preprocessor.
add_definitions(-DHAPPY_ML_VERSION=${HAPPY_ML_VERSION})


###############################################################################
# Testing.                                                                    #
###############################################################################

# Setup CMake to run tests.
enable_testing()

# Run through each test source.
file(GLOB TEST_SOURCES ${TEST_DIR}/*.cpp)
foreach(testSrc ${TEST_SOURCES})
        # Extract the filename without an extension (NAME_WE).
        get_filename_component(testName ${testSrc} NAME_WE)

        # Add compile target.
        add_executable(${testName} ${testSrc})

        # Link to our targets and dependencies.
        target_compile_options(${testName} PRIVATE -pthread)
        set(CMAKE_CXX_FLAGS "-pthread")  # Critical for compiling with Google Tests.
        target_link_libraries(${testName}
            gtest  # Google test library.
            ${PROJECT_SOURCE_DIR}/${LIBRARY_OUTPUT_DIR}/lib${PROJECT_NAME}.so)

        # Finally add it to cmake test execution.
        add_test(NAME ${testName}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${testName})
endforeach(testSrc)
