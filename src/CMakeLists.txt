add_library(InvertedIndex STATIC
    InvertedIndex.cpp
)

target_include_directories(InvertedIndex PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(InvertedIndex PRIVATE project_warnings)
find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
    file(GLOB_RECURSE FORMAT_SOURCES "*.cpp" "*.hpp")
    add_custom_target(format
        COMMAND ${CLANG_FORMAT} -i ${FORMAT_SOURCES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Formatting source files"
    )
endif()