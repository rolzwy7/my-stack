#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

namespace Mobs {

	class Monster {

	public:
		void printStats() {
			cout << "Name    : " << this->type << " " << this->name << "\n";
			cout << "Species : " << this->species << "\n";
			cout << "Health  : " << this->hp << "\n";
			cout << "Attack  : " << this->attack << "\n";
			cout << "Defense : " << this->defense << "\n";
			cout << "Alive   : " << this->alive << "\n\n";
		}

	protected:
		string name;
		string species;
		string type;
		float hp;
		float attack;
		float defense;
		bool alive = true;

		Monster(float hp, float attack, float defense) {
			this->hp = hp;
			this->attack = attack;
			this->defense = defense;
		}

		~Monster() {
			cout << "Dead Boi:" << this->name << "\n";
		}

		void damage(float dmg) {
			this->hp -= dmg;
			if (this->isDead())
				this->kill();
		}

		bool isDead() {
			return (this->hp <= 0) ? true : false;
		}

		void kill() {
			this->alive = false;
		}

	};

	class BlackOrc : public Monster {
		public:
			BlackOrc(float hp, float attack, float defense)
				:Monster(hp, attack, defense) {
				this->name			= "Black Orc";
				this->species		= "Orc";
				this->type			= "Evil";
			}
	};

	class Goblin : public Monster {
		public:
			Goblin(float hp, float attack, float defense)
				:Monster(hp, attack, defense) {
				this->name = "Goblin";
				this->species = "Orc";
				this->type = "Green";
			}
	};

	class Wyvern : public Monster {
		public:
			Wyvern(float hp, float attack, float defense)
				:Monster(hp, attack, defense) {
				this->name = "Wyvern";
				this->species = "Beast";
				this->type = "Ancient";
			}
	};

} // namespace Mobs

int main() {
	Mobs::BlackOrc black_orc_1(840, 70, 150);
	Mobs::Goblin goblin_1(120, 10, 25);
	Mobs::Wyvern wyvern_1(5000, 150, 450);


	black_orc_1.printStats();
	goblin_1.printStats();
	wyvern_1.printStats();

    return 0;
}

