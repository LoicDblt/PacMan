#!/bin/bash

# Mets les fichiers de CMake dans un dossier spécifique
# Puis construit le projet en nettoyant d'abord

# Si l'argument est "clean", nettoie le projet

if [ $# -gt 1 ];
then
	echo "Error: too much arguments"
	echo "Usage: sh $0 [clean]"
	exit 1
fi

if [ $# -eq 1 ] && [ "$1" != "clean" ];
then
	echo "Error: wrong argument"
	echo "Usage: sh $0 [clean]"
	exit 1
fi

if [ "$1" = "clean" ];
then
	rm -rf build PacMan
	echo "Project cleaned"
else
	cmake -S . -B build
	cmake --build build --clean-first
fi