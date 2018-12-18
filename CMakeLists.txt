# Generated on 2018-12-18 22:43:21 by version 0.7.0 of mulle-xcode-to-cmake
# Command line:
#    mulle-xcode-to-cmake -b export Nectarine.xcodeproj

project( Nectarine)

cmake_minimum_required (VERSION 3.4)


##
## Nectarine Files
##

# uncomment this for mulle-objc to search libraries first
# set( CMAKE_FIND_FRAMEWORK "LAST")

set( SOURCES
Nectarine/NectCompiler/NectCompiler.cpp
Nectarine/NectCompiler/NectStack.cpp
Nectarine/NectExpression/NectExpression.cpp
Nectarine/NectStatement/NectStatement.cpp
Nectarine/main.cpp
)

find_library( BOOST_SYSTEM_LIBRARY boost_system)
message( STATUS "BOOST_SYSTEM_LIBRARY is ${BOOST_SYSTEM_LIBRARY}")

set( STATIC_DEPENDENCIES
${BOOST_SYSTEM_LIBRARY}
)

find_library( FOUNDATION_LIBRARY Foundation)
message( STATUS "FOUNDATION_LIBRARY is ${FOUNDATION_LIBRARY}")

set( DEPENDENCIES
${FOUNDATION_LIBRARY}
)


##
## Nectarine
##

add_executable( Nectarine MACOSX_BUNDLE
${SOURCES}
${PUBLIC_HEADERS}
${PROJECT_HEADERS}
${PRIVATE_HEADERS}
${RESOURCES}
)

target_include_directories( Nectarine
   PUBLIC
)

target_link_libraries( Nectarine
${STATIC_DEPENDENCIES}
${DEPENDENCIES}
)
