cmake_minimum_required(VERSION 3.5)

project(FskDemod LANGUAGES CXX)
if(UNITTEST)
        add_subdirectory(googletests/)
endif()
add_subdirectory(sourse/FileManager)
add_subdirectory(sourse/Pll)
add_subdirectory(sourse/Demodulator)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FskDemod main.cpp)

target_link_libraries(${PROJECT_NAME} Demodulator)
