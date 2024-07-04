cmake_minimum_required(VERSION 3.10)

project(intell_parking)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC on)
# 指定头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_BINARY_DIR}/src CPP_SOURCE)

add_executable(${PROJECT_NAME}
        ${CPP_SOURCE}
        ${PROJECT_BINARY_DIR}/include
)   

# 通过cmake 搜索特定库
find_package(Qt5 COMPONENTS Widgets)
find_package(OpenCV 4.2.0 REQUIRED)

# 链接所需要的库文件
target_link_libraries(${PROJECT_NAME} 
    # /usr/lib/libxxx.so
    Qt5::Widgets
    ${OpenCV_LIBS}
)