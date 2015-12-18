
cmake_minimum_required(VERSION 2.8.9)
project(happyml CXX)
set(HAPPY_ML_VERSION "1.0")
set(INCLUDE_DIR "include")
set(SOURCES_DIR "src")
set(LIBRARY_OUTPUT_DIR "lib")

# Including header files at include dir.
include_directories(${INCLUDE_DIR})

# ALL cpp files under src.
file(GLOB SOURCES "${SOURCES_DIR}/*.cpp")

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

#Setup CMake to run tests
enable_testing()

#I like to keep test files in a separate source directory called test
file(GLOB TEST_SOURCES "test/*.cpp")

#Run through each source
foreach(testSrc ${TEST_SOURCES})
        # Extract the filename without an extension (NAME_WE)
        get_filename_component(testName ${testSrc} NAME_WE)

        # Add compile target
        add_executable(${testName} ${testSrc})

        # Link to our targets and dependencies.
        target_compile_options(${testName} PUBLIC -pthread)
        set(CMAKE_CXX_FLAGS "-pthread")
        target_link_libraries(${testName}
            #${CMAKE_THREAD_LIBS_INIT}  # Threads management. Put it before gtest!
            gtest    # Google test library.
            ${PROJECT_SOURCE_DIR}/${LIBRARY_OUTPUT_DIR}/lib${PROJECT_NAME}.so)

        # I like to move testing binaries into a testBin directory
        set_target_properties(${testName} PROPERTIES 
            RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_BINARY_DIR}/bin/test)
        #add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
        #    DEPENDS ${testSrc})

        # Finally add it to test execution - 
        # Notice the WORKING_DIRECTORY and COMMAND
        add_test(NAME ${testName} 
                 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/test 
                 COMMAND ${PROJECT_BINARY_DIR}/bin/test/${testName} )
endforeach(testSrc)
