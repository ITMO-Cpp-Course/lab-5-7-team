add_library(InvertedIndex STATIC
    InvertedIndex.cpp
)

target_include_directories(InvertedIndex PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(InvertedIndex PRIVATE project_warnings)