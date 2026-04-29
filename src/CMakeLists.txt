add_library(Document STATIC
        Document.cpp
        IndexError.hpp
)

add_library(DocumentBuilder STATIC
        DocumentBuilder.cpp
)

add_library(InvertedIndex STATIC
        InvertedIndex.cpp
)

target_link_libraries(DocumentBuilder PRIVATE Document)
target_link_libraries(InvertedIndex PRIVATE Document DocumentBuilder project_warnings)

target_include_directories(Document PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(DocumentBuilder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(InvertedIndex PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (ENABLE_SANITIZERS AND NOT WIN32)
    target_link_libraries(InvertedIndex PRIVATE project_sanitizers)
endif()