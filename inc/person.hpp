#ifndef PERSON_H
#define PERSON_H

#include <cstdlib>
#include <iostream>
#include <list>

#include "coordinate.hpp"
#include "entity.hpp"

class Person : public Entity {
	/* Variables et constantes */
	public:
		enum Direction {UP, DOWN, RIGHT, LEFT, NONE};
		enum CaracterType {PACMAN, GRED, GPINK, GBLUE, GORANGE};

	private:
		float speed_;
		Direction direction_;
		Direction wishDirection_;
		int healthPoints_;
		int tryToTurnCmp_{50};
		int tmpAnimation_{0};
		std::vector<SDL_Rect> up_;
		std::vector<SDL_Rect> down_;
		std::vector<SDL_Rect> left_;
		std::vector<SDL_Rect> right_;
		bool outSpawn_{true};


	/* Constructeurs et destructeur */
	public:
		Person() = default;
		~Person() = default;
		Person(
			SDL_Rect entityRect,
			SDL_Rect entityPicture,
			float speed,
			Direction direction,
			Direction wishDirection,
			int healthPoints,
			bool outSpawn,
			std::vector<SDL_Rect> up,
			std::vector<SDL_Rect> down,
			std::vector<SDL_Rect> left,
			std::vector<SDL_Rect> right
		);


	/* Getters */
	public:
		inline Direction getDirection(void) const {
			return direction_;
		}

		inline int getHelthPoints(void) const {
			return healthPoints_;
		}

		inline bool getOutSpawn(void) const {
			return outSpawn_;
		}


	/* Setters */
	public:
		inline void setEntityRect(SDL_Rect entityRect) {
			entityRect_ = entityRect;
		}

		inline void setDirection(Direction direction) {
			direction_ = direction;
		}

		inline void setWishDirection(Direction wishDirection) {
			wishDirection_ = wishDirection;
		}

		inline void setHelthPoints(int healthPoints) {
			healthPoints_ = healthPoints;
		}

		inline void setAnimation(
			std::vector<SDL_Rect> left,
			std::vector<SDL_Rect> right,
			std::vector<SDL_Rect> up,
			std::vector<SDL_Rect> down
		) {
			left_ = left;
			right_ = right;
			up_ = up;
			down_ = down;
		}

		inline void setOutSpawn(void) {
			outSpawn_ = true;
		}


	/* Méthodes */
	public:
		inline void lostHelthPoint(void) {
			healthPoints_ -= 1;
		}

	public:
		/**
		 * @brief Déplace le personnage si la direction est accessible, ou le
		 * 		  téléporte s'il emprunte un tunnel
		 *
		 * @param walls
		 * @param tunnels
		 */
		void move(std::vector<SDL_Rect> &walls, std::vector<SDL_Rect> &tunnels);

		/**
		 * @brief Effectue les différentes animations
		 *
		 * @param count compteur du nombre de tours
		 */
		void animation(int count);

	private:
		/**
		 * @brief Vérifie si il y a un mur dans la direction donnée
		 *
		 * @param walls les murs présents sur la carte
		 * @param entity le personnage (Pac-Man ou les fantômes)
		 * @return true s'il y a un mur
		 * @return false s'il n'y a pas de mur
		 */
		bool checkWalls(std::vector<SDL_Rect> &walls, SDL_Rect &entity);

	protected:
		/**
		 * @brief Vérifie si la direction est accessible
		 *
		 * @param walls les murs présents sur la carte
		 * @param direction souhaitée
		 * @return true si la direction est accessible
		 * @return false si la direction n'est pas accessible
		 */
		bool checkDirection(std::vector<SDL_Rect> &walls, Direction direction);

		/**
		 * @brief Retourne une liste des directions possibles
		 *
		 * @param walls les murs présents sur la carte
		 * @param validDirection la liste des directions possibles
		 */
		void intersectionDirection(
			std::vector<SDL_Rect> &walls,
			std::list<Direction> &validDirection
		);

		/**
		 * @brief Vérifie si le personnage est sorti de la zone de spawn
		 *
		 * @return true s'il a franchi la porte
		 * @return false s'il n'a pas franchi la porte
		 */
		bool checkOutSpawn(void);
};

#endif