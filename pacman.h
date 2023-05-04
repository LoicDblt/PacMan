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
 * @param player Pac-Man
 * @param red fantôme rouge
 * @param blue fantôme bleu
 * @param pink fantôme rose
 * @param orange fantôme orange
 * @param statsPac les stats à afficher
 */
void initGame(
	Player &player,
	Ghost &red,
	Ghost &blue,
	Ghost &pink,
	Ghost &orange,
	Stats &statsPac
);

/**
 * @brief Replace les dots, energizers, ghosts à leur position d'origine
 *
 * @param player Pac-Man
 * @param red fantôme rouge
 * @param blue fantôme bleu
 * @param pink fantôme rose
 * @param orange fantôme orange
 * @param statsPac les stats à afficher
 */
void resetGame(
	Player &Player,
	Ghost &red,
	Ghost &blue,
	Ghost &pink,
	Ghost &orange,
	Stats &statsPac
);

/**
 * @brief Mets à jour la fenêtre de jeu
 *
 */
void draw(void);

#endif