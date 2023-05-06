# Défini le standard à appliquer
set(CMAKE_CXX_STANDARD 17)

# Ajoute le dossier des headers
include_directories(${PROJECT_SOURCE_DIR}/inc)

# Défini le nom de l'exécutable et son emplacement
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})


# Ajoute la librairie SDL2
find_package(SDL2 REQUIRED)

# Ajoute les fichiers source
target_sources(${PROJECT_NAME}
	PRIVATE
	entity.cpp
	game.cpp
	ghost.cpp
	interface.cpp
	pacman.cpp
	person.cpp
	player.cpp
	stats.cpp
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
	${SDL2_INCLUDE_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${PROJECT_NAME} PRIVATE "SDL_MAIN_HANDLED")
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

IF (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY
		VS_STARTUP_PROJECT ${PROJECT_NAME})
ENDIF()