cmake_minimum_required(VERSION 2.6)
 
PROJECT(QWT)
 
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
 
QT4_WRAP_UI(UISrcs form.ui)
QT4_WRAP_CPP(MOCSrcs form.h)
 
include_directories(${include_directories} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} /usr/local/qwt-6.1.3/include)
link_directories(/usr/local/qwt-6.1.3/lib)
 
ADD_EXECUTABLE(plot main.cpp form.cpp ${MOCSrcs} ${UISrcs})
TARGET_LINK_LIBRARIES(plot ${QT_LIBRARIES} qwt)

##############################################################

add_executable(updateData updateData.cpp)
target_link_libraries(updateData pqxx pq)
