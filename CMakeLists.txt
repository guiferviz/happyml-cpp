
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
file(GLOB_RECURSE SOURCES ${SOURCES_DIR}/*.cpp)

# Generate the shared library from the sources.
add_library(${PROJECT_NAME} SHARED ${SOURCES})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/${LIBRARY_OUTPUT_DIR})

# External libraries.
find_package(Armadillo REQUIRED)
target_link_libraries(${PROJECT_NAME} m armadillo)

# Location for library installation.
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
install(FILES ${INCLUDE_DIR}/${PROJECT_NAME}.h DESTINATION include)
install(DIRECTORY ${INCLUDE_DIR}/${PROJECT_NAME} DESTINATION include)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/happyplot DESTINATION bin)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/happydatacreator DESTINATION bin)

# Adding definitions to use with the preprocessor.
add_definitions(-DHAPPY_ML_VERSION=\"${HAPPY_ML_VERSION}\")  # Version as a string.


#########################################################################################
# Testing.                                                                              #
#########################################################################################

if (build_tests)
    # Setup CMake to run tests.
    enable_testing()
    # Copy fixture (data for testing) directory to the binary folder.
    add_custom_target(copy_fixture_data ALL)
    add_custom_command(TARGET copy_fixture_data PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_SOURCE_DIR}/${TEST_DIR}/fixtures
                ${PROJECT_BINARY_DIR}/bin/test/fixtures)
    # Google Tests required.
    find_package(GTest REQUIRED)

    # Run through each test source.
    file(GLOB_RECURSE TEST_SOURCES ${TEST_DIR}/*.cpp)
    foreach(testSrc ${TEST_SOURCES})
            # Extract the filename without an extension (NAME_WE).
            get_filename_component(testName ${testSrc} NAME_WE)

            # Add compile target.
            add_executable(${testName} ${testSrc})

            # Link to our targets and dependencies.
            target_compile_options(${testName} PRIVATE -pthread)
            # FIXME: Not multiplatform...
            set(CMAKE_CXX_FLAGS "-pthread")  # Critical for compiling with Google Tests.
            target_link_libraries(${testName}
                gtest  # Google test library.
                ${PROJECT_NAME})

            # Placing binary tests on bin/test
            set_target_properties(${testName} PROPERTIES 
                RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/test)

            # Finally add it to cmake test execution.
            add_test(NAME ${testName}
                WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/bin/test
                COMMAND ${PROJECT_BINARY_DIR}/bin/test/${testName})
    endforeach(testSrc)
endif()


#########################################################################################
# Documentation                                                                         #
#########################################################################################

# Add a target to generate API documentation with Doxygen.
# (thanks Stefan Majewsky for the following code).
find_package(Doxygen)

if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)
