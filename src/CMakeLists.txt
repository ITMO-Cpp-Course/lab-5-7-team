add_library(src STATIC
    Document.cpp
    DocumentBuilder.cpp
    InvertedIndex.cpp
    IndexStore.cpp
    UpdateTransaction.cpp
    Result.cpp
)

target_link_libraries(src PRIVATE project_warnings)
if (TARGET project_sanitizers)
        target_link_libraries(src PRIVATE project_sanitizers)
endif ()

target_include_directories(src
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)