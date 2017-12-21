set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED
    COMPONENTS system filesystem)
if(Boost_FOUND AND Boost_FILESYSTEM_FOUND AND Boost_SYSTEM_FOUND)
else()
    message(FATAL "FindBoost() fails")
endif()

add_library(boost_headers_only INTERFACE IMPORTED)
set_property(TARGET boost_headers_only
    PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS})

add_library(boost_filesystem STATIC IMPORTED)
set_property(TARGET boost_filesystem
    PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS})
set_property(TARGET boost_filesystem
    PROPERTY IMPORTED_LOCATION ${Boost_FILESYSTEM_LIBRARY})

add_library(boost_system STATIC IMPORTED)
set_property(TARGET boost_system
    PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS})
set_property(TARGET boost_system
    PROPERTY IMPORTED_LOCATION ${Boost_SYSTEM_LIBRARY})