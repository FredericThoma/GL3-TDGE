cmake_minimum_required(VERSION 3.18)

set(SOURCE_FILES src/main.cpp src/Player.h src/Score.h src/GameOverScreen.h
        src/MyGame.h
        src/EnemyProjectileCollision.h
)
set(EXE_FILE ExampleGame)

add_executable(${EXE_FILE} ${SOURCE_FILES})

target_compile_features(${EXE_FILE} PRIVATE cxx_std_17)

target_link_libraries(${EXE_FILE} PRIVATE Engine)
