#ifndef STATS_H
#define STATS_H

#include <iostream>
#include <vector>
#include <SDL.h>

class Stats {
	private:
		int pacgomme_{0};
		int superPacgomme_{0};

	/* Constructors */
	public:
		// Default constructor
		Stats() = default;

		~Stats();

		void afficherScore(){
			// 10 points la pacgomme
			// 50 points la super pacgomme
			// 200 points le fantôme (x2 pour chaque fantôme mangé pendant une
			// même période)
			// Fruit :
			//		Cerise : 100 points
			//		Fraise : 200 points
			//		Orange : 500 points
			//		Pomme : 700 points
			//		Melon : 1000 points
			//		Galboss : 2000 points
			//		Cloche : 3000 points
			//		Clé : 5000 points
			std::cout << getPacG()*10 << std::endl;
		}

	/* Getter */
	public:
		inline int getPacG() const {
			return pacgomme_;
		}
		inline int getSuperPacG() const {
			return superPacgomme_;
		}

	/* Setter */
	public:
		inline void addPacG(void) {
			pacgomme_++;
		}
		inline void addSuperPacG(void) {
			superPacgomme_++;
		}
};

#endif