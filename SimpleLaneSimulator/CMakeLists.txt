cmake_minimum_required(VERSION 2.8)

project(SimpleLaneSimulator)

find_package(OpenCV REQUIRED)


add_executable(${PROJECT_NAME} "main.cpp" "road.cpp" "road.h" "scenefacade.h" "scenefacade.cpp")
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
