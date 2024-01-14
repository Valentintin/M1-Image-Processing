cmake_minimum_required(VERSION 2.8)
project( main )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
<<<<<<< 818e394b651d6f2be605aecc4bb488619a65d4fd
add_executable( main main.cpp DivImage.cpp Fusion.cpp Region.cpp Video.cpp)
=======
add_executable( main main.cpp DivImage.cpp Fusion.cpp Region.cpp TableThreadAccess.cpp )
>>>>>>> fa6420b71ce1e275b16f2dd6f8107bada67ad913
target_link_libraries( main ${OpenCV_LIBS} )