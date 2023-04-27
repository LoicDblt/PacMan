#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "coordinate.h"
#include "ghost.h"
#include "interface.h"
#include "person.h"
#include "player.h"
#include "stats.h"

/**
 * @brief Initialise le jeu et l'interface
 *
 */
void init();

/**
 * @brief Mets à jour la fenêtre
 *
 */
void draw();