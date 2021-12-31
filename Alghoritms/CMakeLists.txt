cmake_minimum_required(VERSION 2.8)

find_package(OpenCV REQUIRED)
find_package(ALGLIB)

project(Algorithms)
include_directories(".")
add_executable(Derivatives "SecondDerivatives/main.cpp" "utils/mymath.h" "utils/mymath.cpp" "utils/myimageprocessing.h" "utils/myimageprocessing.cpp")
target_link_libraries(Derivatives ${OpenCV_LIBS})

if (${ALGLIB_FOUND})
    add_executable(Opt "3DOptimization/main.cpp" "utils/mymath.h" "utils/mymath.cpp" "utils/myimageprocessing.h" "utils/myimageprocessing.cpp")
    target_link_libraries(Opt ${OpenCV_LIBS} ${ALGLIB_LIB})
endif()
