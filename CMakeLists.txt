############################################################################
# CMakeLists.txt
#
#    Released under the MIT License.  See LICENSE.txt for license information.
#
############################################################################

cmake_minimum_required(VERSION 3.0)
project(DECAF VERSION 0.9.4 LANGUAGES C CXX)

set(DECAF_SO_VERSION "0")

option(ENABLE_SHARED "Build shared library." ON)
option(ENABLE_STATIC "Build static library." ON)
option(ENABLE_STRICT "Build with strict compile options." YES)
option(ENABLE_TESTS  "Enable compilation of tests." YES)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if(NOT CPACK_GENERATOR AND NOT CMAKE_INSTALL_RPATH AND CMAKE_INSTALL_PREFIX)
	set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_FULL_LIBDIR})
	message(STATUS "Setting install rpath to ${CMAKE_INSTALL_RPATH}")
endif()

include(GNUInstallDirs)
include(CheckSymbolExists)
include(CMakePushCheckState)

include_directories(
	src/GENERATED/include/
	src/include/
	src/
	${CMAKE_CURRENT_BINARY_DIR}
)

set(STRICT_OPTIONS_CPP )
set(STRICT_OPTIONS_C )
set(STRICT_OPTIONS_CXX )
set(STRICT_OPTIONS_OBJC )
if(MSVC)
	if(ENABLE_STRICT)
		list(APPEND STRICT_OPTIONS_CPP "/WX")
	endif()
else()
        list(APPEND STRICT_OPTIONS_CXX "-std=c++11 -O2")
	list(APPEND STRICT_OPTIONS_CPP "-Wall -Wuninitialized -Wno-deprecated-declarations -Wno-missing-field-initializers")
	list(APPEND STRICT_OPTIONS_C "-std=c99 -O2 -Wstrict-prototypes -Wno-error=strict-prototypes -ffunction-sections -fdata-sections -fvisibility=hidden -fomit-frame-pointer")
	if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
		list(APPEND STRICT_OPTIONS_CPP "-Qunused-arguments" "-Wno-array-bounds")
	endif()
	if(APPLE)
		list(APPEND STRICT_OPTIONS_CPP "-Wno-error=unknown-warning-option" "-Qunused-arguments" "-Wno-tautological-compare" "-Wno-unused-function" "-Wno-array-bounds")
		list(APPEND STRICT_OPTIONS_CXX "-stdlib=libc++")
	endif()
	if(ENABLE_STRICT)
		list(APPEND STRICT_OPTIONS_CPP "-Werror" "-Wextra" "-Wno-unused-parameter" "-fno-strict-aliasing")
	endif()
endif()
if(STRICT_OPTIONS_CPP)
	list(REMOVE_DUPLICATES STRICT_OPTIONS_CPP)
endif()
if(STRICT_OPTIONS_C)
	list(REMOVE_DUPLICATES STRICT_OPTIONS_C)
endif()

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${STRICT_OPTIONS_C})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${STRICT_OPTIONS_CXX})

add_subdirectory(src)

if(ENABLE_TESTS)
        enable_testing()
	add_subdirectory(test)
endif()

include(CMakePackageConfigHelpers)
export(EXPORT ${EXPORT_TARGETS_NAME}Targets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/decafTargets.cmake"
)
configure_file(cmake/decafConfig.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/decafConfig.cmake"
	@ONLY
)
set(ConfigPackageLocation share/decaf/cmake)
install(EXPORT ${EXPORT_TARGETS_NAME}Targets
	FILE decafTargets.cmake
	DESTINATION ${ConfigPackageLocation}
)
install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/decafConfig.cmake"
	DESTINATION ${ConfigPackageLocation}
)

# CPack settings
set(CPACK_PACKAGE_NAME "decaf")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_SOURCE_IGNORE_FILES
        "^${CMAKE_BINARY_DIR}"
        "/\\\\..+"
)

include(CPack)
