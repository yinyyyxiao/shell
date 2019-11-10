###############################################################################
# CMakeLists.txt for Poc(Distributed Playback) Shell Process
#
# 2017/03/08  新規作成                                          Free Software
################################################################################
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# プロジェクト名
project(csh C)

# リリースビルド用オプション
set(CMAKE_C_FLAGS_RELEASE "-m64 -std=gnu99 -g -Wall -O2")

set(CMAKE_CXX_FLAGS_DEBUG "-m64 -Wall -O -fPIC  -g -Wconversion")

# ビルドのタイプはデバッグ
#set(CMAKE_BUILD_TYPE Release)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/product)

# 静态库设定
set(ARCHIVES
        )

# 动态库设定
set(LIBDEF
        pthread
        readline
        )

# link dir 设定
link_directories(
)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

file(GLOB SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/common/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/shell_c/*.c
        )


SET(LDFLAGS "${LDFLAGS} -Wl,-no-as-needed")

add_executable(${PROJECT_NAME} ${SOURCE})

set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "${CFLAGS}")

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "${LDFLAGS} ${RPATHDEF}")

target_link_libraries(${PROJECT_NAME} ${ARCHIVES})

target_link_libraries(${PROJECT_NAME} ${LIBDEF})

