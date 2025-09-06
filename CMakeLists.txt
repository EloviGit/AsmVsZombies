cmake_minimum_required(VERSION 3.10)
project(AsmVsZombies)

# set global options
add_compile_options(-m32 -std=c++20 -Wall)
add_link_options(-m32)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_library(compile_options INTERFACE)
target_compile_options(compile_options INTERFACE -fexperimental-library)
target_include_directories(compile_options INTERFACE inc)


aux_source_directory(src avz_srcs)
aux_source_directory(src/minhook minhook_srcs)

# build libavz under original pvz
add_library(avz_original ${avz_srcs} ${minhook_srcs})
target_link_libraries(avz_original PRIVATE original compile_options)
target_compile_definitions(avz_original PRIVATE -DPLATFORM_ORIGINAL)

# # build libavz under pvz-emulator
# add_library(avz_pvz_emulator STATIC ${avz_srcs} ${minhook_srcs})
# target_link_libraries(avz_pvz_emulator PRIVATE compile_options)
# target_compile_definitions(avz_pvz_emulator PRIVATE -DPLATFORM_PVZ_EMULATOR)

# build injector
add_subdirectory(tools/injector)

# 此条命令仅用于作者打包 avz，仅编译 avz 请注释这条命令
add_custom_target(PackageAvz ALL
    COMMAND powershell -c "\
        cd '${PROJECT_SOURCE_DIR}'; \
        rm bin/*.dll; \
        Compress-Archive -Path bin/,inc/,src/,metadata.json -Force -DestinationPath release/env2/nightly.zip"
    DEPENDS avz_original injector
)
