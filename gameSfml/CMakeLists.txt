cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 20)



set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)


set(SFML_DIR "C:\\Users\\sakhd\\CLionProjects\\lib\\smfl\\GCC 13.1.0 MinGW (SEH) - 64-bit\\SFML-2.6.1\\lib\\cmake\\SFML")

#find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)
#
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)

add_library(Graphic gameGraphics.cpp gameGraphics.h)

add_executable(testStart testStart.cpp)
target_link_libraries(Graphic sfml-graphics sfml-audio Enemy Dungeon Golem Character LivingEnemy LivingSummoner UndeadSummoner Enemy Game)
target_link_libraries(testStart sfml-graphics sfml-audio Enemy Dungeon Golem Character LivingEnemy LivingSummoner UndeadSummoner Enemy Game Graphic)
