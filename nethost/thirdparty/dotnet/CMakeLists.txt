cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(dotnetHost)

if (WIN32)
    set(DOTNET_SEARCH_PATH "$ENV{ProgramFiles}/dotnet")
else ()
    set(DOTNET_SEARCH_PATH "/usr/share/dotnet" "/usr/local/share/dotnet")
endif ()

if (DEFINED ENV{DOTNET_ROOT})
    set(DOTNET_SEARCH_PATH "$ENV{DOTNET_ROOT}")
endif ()

file(GLOB_RECURSE PACKS_DIRS
        LIST_DIRECTORIES TRUE
        CONFIGURE_DEPENDS
        ${DOTNET_SEARCH_PATH}/packs/*
)

set(VERSION_CANDIDATES ${PACKS_DIRS})
list(FILTER VERSION_CANDIDATES INCLUDE REGEX "Microsoft\\.NETCore\\.App\\.Host.*")
list(SORT VERSION_CANDIDATES COMPARE NATURAL ORDER DESCENDING)


if (VERSION_CANDIDATES)
    list(GET VERSION_CANDIDATES 0 HIGHEST_VERSION_DIR)
    message(STATUS "Selected highest version folder: ${HIGHEST_VERSION_DIR}")

    set(NATIVE_DIRS ${PACKS_DIRS})
    list(FILTER NATIVE_DIRS INCLUDE REGEX "/Microsoft\\.NETCore\\.App\\.Host[^/]+/[^/]+/runtimes/[^/]+/native$")
    list(SORT NATIVE_DIRS COMPARE NATURAL ORDER DESCENDING)

    if (NATIVE_DIRS)
        list(GET NATIVE_DIRS 0 NETHOST_INCLUDE_DIR)
        message(STATUS "Found nethost include directory: ${NETHOST_INCLUDE_DIR}")
    endif ()
endif ()

if (NETHOST_INCLUDE_DIR)
    if (WIN32)
        set(LIB_NAME "nethost.lib")
    else ()
        set(LIB_NAME "libnethost.a")
    endif ()

    file(GLOB NETHOST_LIB_PATH
            CONFIGURE_DEPENDS
            "${NETHOST_INCLUDE_DIR}/${LIB_NAME}"
    )

    if (NETHOST_LIB_PATH)
        message(STATUS "Found nethost library: ${NETHOST_LIB_PATH}")

        add_library(dotnet::nethost UNKNOWN IMPORTED GLOBAL)
        set_target_properties(dotnet::nethost PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${NETHOST_INCLUDE_DIR}"
                IMPORTED_LOCATION "${NETHOST_LIB_PATH}"
        )
    else ()
        unset(NETHOST_INCLUDE_DIR)
    endif ()
endif ()

if (NOT NETHOST_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find .NET AppHost Library or Includes")
endif ()
