

add_compile_options(-fprofile-arcs -ftest-coverage)

add_executable(tests testing.cpp)




target_link_libraries(tests gcov Enemy Dungeon Golem Character LivingEnemy LivingSummoner UndeadSummoner Game)