# Permet de clean si ça a déjà été build
DIR="./build"
if [ -d "$DIR" ];
then
	cd ./build
	make clean
	cd ../
fi

# Créé le dossier build s'il n'existait pas
mkdir -p build
cd build

# Compile
cmake -S ../ -B ./
cmake --build ./