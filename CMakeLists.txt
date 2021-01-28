cmake_minimum_required (VERSION 3.10)

project (QRScanner)

set(CMAKE_MODULE_PATH ${QRScanner_SOURCE_DIR})
find_package (OpenCV)
find_package (zbar)

add_executable (qr qr.cpp)
target_link_libraries (qr ${OpenCV_LIBRARIES} ${ZBAR_LIBRARIES})