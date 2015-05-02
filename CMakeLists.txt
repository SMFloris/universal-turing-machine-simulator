cmake_minimum_required(VERSION 2.6)
project(uturingmachine)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(uturingmachine_SRCS trecere.cpp stare.cpp banda.cpp masinaturinguniversala.cpp uturingmachine.cpp main.cpp)

qt4_automoc(${uturingmachine_SRCS})
add_executable(uturingmachine ${uturingmachine_SRCS})
target_link_libraries(uturingmachine ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS uturingmachine RUNTIME DESTINATION bin)
