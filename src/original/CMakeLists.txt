# build original
aux_source_directory(. original_srcs)
add_library(original STATIC ${original_srcs})
target_link_libraries(original compile_options)
target_include_directories(original PRIVATE ${PROJECT_SOURCE_DIR}/inc)
