cmake_minimum_required(VERSION 3.7)

project(PacMan LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} "")
target_sources(${PROJECT_NAME}
		PRIVATE
		person.cpp
		entity.cpp
		stats.cpp
		coordinate.h
		person.h
		entity.h
		stats.h
		pacman.cpp
		)

target_include_directories(${PROJECT_NAME}
		PRIVATE
		${SDL2_INCLUDE_DIRS}
		${CMAKE_CURRENT_SOURCE_DIR}
		)

target_compile_definitions(${PROJECT_NAME} PRIVATE "SDL_MAIN_HANDLED")
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/pacman_sprites.bmp
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

IF (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
ENDIF()