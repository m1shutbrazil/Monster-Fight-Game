#include <iostream>
#include <array>
#include <random>
#include <ctime>

using namespace std;
int getRandomNumber(int min, int max) {
	static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };

	return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

class Creature {
protected:
	string name;
	char symbol;
	int health;
	int damage;
	int gold;
public:
	Creature(const string& name, const char& symbol, const int& health, const int& damage, const int& gold) {
		this->name = name;
		this->symbol = symbol;
		this->health = health;
		this->damage = damage;
		this->gold = gold;
	}

	string getName() const { return name; }
	char getSymbol() const { return symbol; }
	int getHealth() const { return health; }
	int getDamage() const { return damage; }
	int getGold() const { return gold; }

	void reduceHealth(int damage) { this->health -= damage; }
	bool isDead() { return health <= 0; }
	void addGold(int money) { this->gold += money; }
};

class Player : public Creature {
private:
	int level{ 1 };

public:
	Player(const string& name, const char& symbol = '@', const int& health = 10, const int& damage = 1, const int& gold = 0)
		: Creature{ name, '@', 10, 1, 0 } {

	}
	int getLevel() { return level; }

	void Levelup() {
		this->level++;
		this->damage++;
	}

	bool hasWon() { return level >= 20; }
	void drinkPotion() {}
};

class Monster : public Creature {
public:
	enum Type {
		dragon,
		orc,
		slime,

		max_types
	};
private:

	static const Creature& getDefaultCreature(Type type) {
		static std::array<Creature, static_cast<std::size_t>(Type::max_types)> monsterData{
		  { { "orc", 'o', 4, 2, 25 },
			{ "dragon", 'd', 20, 4, 100 },
			{ "slime", 's', 1, 1, 10 }
		  }
		};

		return monsterData.at(static_cast<std::size_t>(type));
	}
public:
	Monster(Type type) : Creature{ getDefaultCreature(type) } {}
	
	static Monster getRandomMonster() {
		int num{ getRandomNumber(0, static_cast<int>(max_types) - 1) };
		return { static_cast<Type>(num) };
	}
};

void attackMonster(Player& player, Monster& monster);
void attackPlayer(Monster& monster, Player& player);

void fightMonster(Player& player) {
	Monster m{ Monster::getRandomMonster() };
	cout << "You have encountered a " << m.getName() << m.getSymbol() << '\n';

	while (!player.isDead() && !m.isDead()) {
		cout << "(R)un or (F)ight: ";
		char choice;
		cin >> choice;
		if (choice == 'R' || choice == 'r') {
			int chance = rand() % 2 + 1;
			if (chance == 1) {
				cout << "You failed to flee.";
				attackPlayer(m, player);
				continue;
			}
			else if (chance == 2) {
				cout << "You successfully fled.";
				return;
			}
		}
		else if (choice == 'F' || choice == 'f') {
			attackMonster(player, m);
			attackPlayer(m, player);
		}
	}
}

void attackMonster(Player& player, Monster& monster) {
	if (player.isDead())
		return;

	cout << "You hit the " << monster.getName() << " for " << player.getDamage() << " damage.\n";
	monster.reduceHealth(player.getDamage());

	if (monster.isDead()) {
		cout << "You killed " << monster.getName() << '\n';
		player.Levelup();
		cout << "You are now level " << player.getLevel() << ".\n";
		cout << "You found " << monster.getGold() << " gold.\n";
		player.addGold(monster.getGold());
	}
}
void attackPlayer(Monster& monster, Player& player) {
	if (monster.isDead())
		return;

	cout << "The " << monster.getName() << " hit you for " << monster.getDamage() << " damage.\n";
	player.reduceHealth(monster.getDamage());
}


int main() {
	srand(time(NULL));

	cout << "Enter your name: ";
	string playerName;
	cin >> playerName;

	Player player{ playerName };
	cout << "Welcom, " << playerName << ".\n";
	cout << "You have " << player.getHealth() << " health and are carrying " << player.getGold() << " gold.";

	while (!player.isDead() && !player.hasWon()) {
		fightMonster(player);
		if (player.isDead()) {
			cout << "You died at level " << player.getLevel() << " and with " << player.getGold() << " gold.\n";
			cout << "Too bad you can't take it with you!";
		}
		else if (player.hasWon()) {
			cout << "Congratulation! You won at level " << player.getLevel() << " and with " << player.getGold() << " gold.\n";
		}

	}

	return 0;
}

