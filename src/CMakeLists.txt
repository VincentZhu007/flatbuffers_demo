set(MONSTER_SCHEMA "${CMAKE_CURRENT_LIST_DIR}/monster.fbs")
set(MONSTER_GENERATED_HEADER monster_generated.h)
set(MONSTER_GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(OUTPUT ${MONSTER_GENERATED_HEADER}
    COMMAND flatc --cpp -o ${MONSTER_GENERATED_DIR} ${MONSTER_SCHEMA}
    DEPENDS ${MONSTER_SCHEMA} flatc
)
add_custom_target(gen_monster_fbs DEPENDS ${MONSTER_GENERATED_HEADER})

add_executable(flatbuffers_demo flatbuffers_demo.cpp)
target_link_libraries(flatbuffers_demo PRIVATE flatbuffers)
target_include_directories(flatbuffers_demo PRIVATE ${MONSTER_GENERATED_DIR})
add_dependencies(flatbuffers_demo gen_monster_fbs)