cmake_minimum_required(VERSION 3.7)

project(PacMan LANGUAGES CXX)

add_subdirectory(src)

file(COPY ${PROJECT_SOURCE_DIR}/asset/pacman_sprites.bmp
	DESTINATION ${PROJECT_SOURCE_DIR}/bin)
