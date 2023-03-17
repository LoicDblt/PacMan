# Créé le dossier build s'il n'existait pas
mkdir -p build
cd build

# Compile en nettoyant d'abord
cmake -S ../ -B ./
cmake --build ./ --clean-first