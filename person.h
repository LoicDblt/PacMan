#ifndef PERSON_H
#define PERSON_H

#include <cstdlib>
#include <iostream>
#include <list>

#include "entity.h"

class Person : public Entity {
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

	/* Constructors */
	public:
		Person() = default;
		Person(
			float speed,
			enum Direction direction
		);
		Person(
			SDL_Rect entityRect,
			SDL_Rect entityPicture,
			float speed,
			Direction direction,
			Direction wishDirection,
			int healthPoints
		);
		Person(
			SDL_Rect entityRect,
			SDL_Rect entityPicture,
			float speed,
			Direction direction,
			Direction wishDirection,
			int healthPoints,
			std::vector<SDL_Rect> up,
			std::vector<SDL_Rect> down,
			std::vector<SDL_Rect> left,
			std::vector<SDL_Rect> right
		);
		~Person();

	/* Methods */
	private:
		bool checkWalls(std::vector<SDL_Rect> &walls, SDL_Rect &entity);
		
	protected:
		/* TRUE if direction available */
		bool checkDirection(std::vector<SDL_Rect> &walls, Direction direction);
		/* Intersection Direction */
		void intersectionDirection(std::vector<SDL_Rect> &walls,
			std::list<Direction> &validDirection);


	public:
		void move(std::vector<SDL_Rect>& walls, std::vector<SDL_Rect>& tunnels);
		void animation(int count);

	/* Getter */
	public:
		inline Direction getDirection() const {
			return direction_;
		}

		inline int getLives() const {
			return healthPoints_;
		}

	/* Setter */
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

		inline void lostLive(void) {
			healthPoints_ -= 1;
		}
		inline void setAnimation(
			std::vector<SDL_Rect> left, 
			std::vector<SDL_Rect> right, 
			std::vector<SDL_Rect> up,
			std::vector<SDL_Rect> down)
		{
			left_ = left;
			right_ = right;
			up_ = up;
			down_ = down;
		}
};

#endif