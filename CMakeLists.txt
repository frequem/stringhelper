cmake_minimum_required(VERSION 3.10)

project(stringhelper C)

option(ENABLE_TESTING "enable testing" OFF)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS_DEBUG "-O3 -g -Werror -pedantic-errors -Wall -Wextra -Wno-sign-compare")
set(CMAKE_C_FLAGS_RELEASE "-O3")

file(GLOB_RECURSE SOURCES "src/*.c")
file(GLOB_RECURSE HEADERS "include/${PROJECT_NAME}/*.*")
add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

if(ENABLE_TESTING)
	enable_testing()
	
	set(THREADS_PREFER_PTHREAD_FLAG ON)
	find_package(Threads REQUIRED)

	file(GLOB_RECURSE TEST_MAINSOURCES "test/test_*.c")
	file(GLOB_RECURSE TEST_SOURCES "test/*.c")
	list(REMOVE_ITEM TEST_SOURCES ${TEST_MAINSOURCES})

	foreach(file ${TEST_MAINSOURCES})
		get_filename_component(name ${file} NAME_WE)
		add_executable(${name} ${file} ${TEST_SOURCES})
		string(SUBSTRING ${name} 5 -1 shortname)
		target_link_libraries (${name} LINK_PUBLIC ${PROJECT_NAME} Threads::Threads)
		add_test(NAME ${shortname} COMMAND ${name})
	endforeach()
endif()

include(GNUInstallDirs)

install(
	TARGETS ${PROJECT_NAME}
	EXPORT "${PROJECT_NAME}Targets"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(
	DIRECTORY "include/${PROJECT_NAME}"
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file("${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION 1.0.5
  COMPATIBILITY AnyNewerVersion
)

install(
	FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake"
		"${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

install(
	EXPORT "${PROJECT_NAME}Targets"
	FILE "${PROJECT_NAME}Targets.cmake"
	NAMESPACE "${PROJECT_NAME}::"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)
