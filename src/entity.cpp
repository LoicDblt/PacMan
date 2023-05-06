#include "entity.hpp"

Entity::Entity(
	SDL_Rect entityRect,
	SDL_Rect entityPicture
):
	entityRect_{entityRect},
	entityPicture_{entityPicture}
{}

int Entity::randGenInterval(int x, int y) {
	std::random_device rdm;							// Nbr aléatoire du hardware
	std::mt19937 gen(rdm());						// Génère une graine
	std::uniform_int_distribution<int> distr(x, y);	// Défini l'intervalle

	return distr(gen);
}