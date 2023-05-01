#ifndef PACMAN_H
#define PACMAN_H

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
 * @param player pacman
 * @param red fantôme rouge
 * @param pink fantôme rose
 * @param blue fantôme bleu
 * @param orange fantôme orange
 */
void init(Player &player, Ghost &red, Ghost &pink, Ghost &blue, Ghost &orange);

/**
 * @brief Remet les dots, energizers, ghosts à leur position
*/
void resetGame(void);

/**
 * @brief Mets à jour la fenêtre
 *
 */
void draw(void);

#endif