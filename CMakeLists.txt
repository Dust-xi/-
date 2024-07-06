cmake_minimum_required(VERSION 3.10)

# 配置C++标准
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

project(intell_parking)

# 启用Qt的自动MOC、UIC和RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/easypr)  # 包含easyPR的头文件

# 将源文件导出
aux_source_directory(${PROJECT_SOURCE_DIR}/src CPP_SOURCE)
message("name 3: ${CPP_SOURCE}")
# 查找Qt5 Widgets模块
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# 查找OpenCV库
find_package(OpenCV 4.2.0 REQUIRED)
# 搜索MySQL库
find_package(Qt5Sql REQUIRED)
# 创建可执行文件
add_executable(${PROJECT_NAME}
    # ${CPP_SOURCE}
    src/main.cpp
    ${PROJECT_SOURCE_DIR}/include/MyWindow.h
    ${PROJECT_SOURCE_DIR}/src/MyWindow.cpp
    ${PROJECT_SOURCE_DIR}/include/DataBase.h
    ${PROJECT_SOURCE_DIR}/src/DataBase.cpp
    ${PROJECT_SOURCE_DIR}/include/Picture.h
    ${PROJECT_SOURCE_DIR}/src/Picture.cpp
    ${PROJECT_SOURCE_DIR}/include/Recognition.h
    ${PROJECT_SOURCE_DIR}/src/Recognition.cpp
)
# 链接库目录
link_directories(${PROJECT_SOURCE_DIR}/lib)
message("sss"${PROJECT_SOURCE_DIR},${PROJECT_NAME} )
# 链接所需的库文件
target_link_libraries(${PROJECT_NAME} 
    Qt5::Widgets
    ${OpenCV_LIBS}
    Qt5::Sql
    ${PROJECT_SOURCE_DIR}/lib/libeasypr.so
    ${PROJECT_SOURCE_DIR}/lib/libthirdparty.a
)
