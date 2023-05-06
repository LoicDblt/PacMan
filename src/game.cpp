#include "game.hpp"

void Game::initGame(
	Player &player,
	std::vector<Ghost> &ghosts,
	Stats &statsPac,
	Interface &interface
) {
	// Créé la fenêtre de jeu
	interface.setWindow(SDL_CreateWindow(Game::GAME_NAME.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		Interface::WINDOW_WIDTH, Interface::WINDOW_HEIGHT, SDL_WINDOW_SHOWN));

	interface.setSurface(SDL_GetWindowSurface(interface.getWindow()));
	interface.setSprites(SDL_LoadBMP(Interface::SPRITE_FILE.c_str()));

	// Initialise les murs avec mise à l'échelle
	for (int i{0}; i < this->getWalls().size(); i++) {
		this->getWalls()[i].x *= 4;
		this->getWalls()[i].y = 4 * (this->getWalls()[i].y) + 100;
		this->getWalls()[i].w *= 4;
		this->getWalls()[i].h *= 4;
	}

	// Initialise les tunnels avec mise à l'échelle
	for (int i{0}; i < this->getTunnels().size(); i++) {
		this->getTunnels()[i].x *= 4;
		this->getTunnels()[i].y = 4 * (this->getTunnels()[i].y) + 100;
		this->getTunnels()[i].w *= 4;
		this->getTunnels()[i].h *= 4;
	}

	resetGame(player, ghosts, statsPac);
}

void Game::resetGame(
	Player &player,
	std::vector<Ghost> &ghosts,
	Stats &statsPac
) {
	// Intialise le compteur
	this->setCount(0);

	// Initialise les Pacgommes
	this->resetDots();
	for (int i{0}; i < this->getDots().size(); i++) {
		this->getDots()[i].x = 4 * (this->getDots()[i].x + 1);
		this->getDots()[i].y = 4 * (this->getDots()[i].y + 1) + 100;
		this->getDots()[i].w *= 8;
		this->getDots()[i].h *= 8;
	}

	// Initialise les super Pacgommes
	this->resetEnergizers();
	for (int i{0}; i < this->getEnergizers().size(); i++) {
		this->getEnergizers()[i].x = 4 * (this->getEnergizers()[i].x + 1);
		this->getEnergizers()[i].y = 4 * (this->getEnergizers()[i].y + 1) + 100;
		this->getEnergizers()[i].w *= 4;
		this->getEnergizers()[i].h *= 4;
	}

	// Réinitialise les personnages à leur état d'origine
	player = Player::initPacMan();
	ghosts = Ghost::initGhosts();

	// Réinitialise les statistiques
	statsPac.resetDotsEaten();
	statsPac.resetEnergizersEaten();
	statsPac.resetGhostsEaten();
}

void Game::draw(Interface &interface) {
	SDL_SetColorKey(interface.getSprites(), false, 0);
	SDL_Rect background = Game::BACKGROUND;
	SDL_BlitScaled(interface.getSprites(), &Coordinate::backMap[0],
		interface.getSurface(), &background);

	// Couleur transparente
	SDL_SetColorKey(interface.getSprites(), true, 0);

	this->setCount((this->getCount() + 1) % (2048));

	// Affichage Pacgommes
	for (int i{0}; i < this->getDots().size(); i++) {
		SDL_BlitScaled(interface.getSprites(), &Coordinate::dotsTexture,
			interface.getSurface(), &this->getDots()[i]);
	}

	// Affichage du fruit
	SDL_BlitScaled(interface.getSprites(), &Coordinate::cherry[0],
		interface.getSurface(), &this->getFruit());


	// Affichage Super Pacgommes
	for (int i{0}; i < this->getEnergizers().size(); i++) {
		SDL_BlitScaled(interface.getSprites(), &Coordinate::energizerTexture,
			interface.getSurface(), &this->getEnergizers()[i]);
	}

	// Affichage du "SCORE"
	SDL_Rect letterPosition{Coordinate::alphabetTexture};

	for (int i: Coordinate::indexScore) {
		SDL_BlitScaled(interface.getSprites(), &Coordinate::alphabet[i],
			interface.getSurface(), &letterPosition);
		letterPosition.x += Coordinate::ALPHABET_TEXTURE_WIDTH;
	}
}

void Game::genFruit(void) {
	int fruitIndex = Entity::randGenInterval(0,
		this->getDots().size() - 1);

	// Mets à l'échelle
	SDL_Rect buffFruit = this->getDots()[fruitIndex];
	buffFruit.x -= buffFruit.w + 4;
	buffFruit.y -= buffFruit.h + 4;
	buffFruit.w *= 4;
	buffFruit.h *= 4;
	this->setFruit(buffFruit);

	this->getDots().erase(this->getDots().begin() + fruitIndex);
}