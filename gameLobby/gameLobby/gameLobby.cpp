#include <iostream>
#include <string>

class Player {
public:
	Player (const std::string name = " ");
	std::string getName() const;
	Player* getNext() const;
	void setNext(Player* next);
private:
	std::string m_Name;
	Player* m_pNext;
};

Player::Player (const std::string name):m_Name(name), m_pNext(0) {

}

std::string Player::getName() const {
	return m_Name;
}

Player* Player::getNext() const {
	return m_pNext;
}

void Player::setNext(Player* next) {
	m_pNext = next;
}

class Lobby {
	friend std::ostream& operator<<(std::ostream& os, const Lobby& aLobby);
public:
	Lobby ();
	~Lobby ();
	void addPlayer();
	void removePlayer();
	void Clear();
private:
	Player* m_pHead;
};

Lobby::Lobby():m_pHead(0) {

}

Lobby::~Lobby() {
	Clear();
}

int main() {
	Lobby myLobby;
	int choice;

	do {
		std::cout << myLobby;
		std::cout << "\nGAME LOBBY\n";
		std::cout << "Press 0 to exit.\n";
		std::cout << "1 - Add a player to the lobby.\n";
		std::cout << "2 - Remove a player from the lobby.\n";
		std::cout << "3 - Clear the lobby.\n";
		std::cout << std::endl << "Enter your choice: ";

		std::cin >> choice;

		switch (choice) {
		case 0: 
			std::cout << "Goodbye.\n";
			break;
		case 1:
			myLobby.addPlayer();
			break;
		case 2:
			myLobby.removePlayer();
			break;
		case 3:
			myLobby.Clear();
			break;
		default:
			std::cout << "That is not a valid choice.\n";
			break;
		}
	} while (choice != 0);

	return 0;
}

void Lobby::addPlayer() {
	std::cout << "Enter the name of the new player: ";
	std::string name;
	std::cin >> name;

	Player* pNewPlayer = new Player(name);

	if (m_pHead == 0) {
		m_pHead = pNewPlayer;
	}
	else {
		Player* pIter = m_pHead;
		while (pIter->getNext() != 0) {
			pIter = pIter->getNext();
		}
		pIter->setNext(pNewPlayer);
	}

}

void Lobby::removePlayer() {
	if (m_pHead == 0) {
		std::cout << "The game lobby is empty. No one to remove!\n";
	}
	else {
		Player* pTemp = m_pHead;
		m_pHead = m_pHead->getNext();
		
		delete pTemp;
	}
}

void Lobby::Clear() {
	while (m_pHead != 0) {
		removePlayer();
	}
}

std::ostream& operator<<(std::ostream& os, const Lobby& aLobby) {
	Player* pIter = aLobby.m_pHead;
	os << "\nHere's who's in the game lobby:\n";

	if (pIter == 0) {
		os << "The lobby is empty.\n";
	}
	else {
		while (pIter != 0) {
			os << pIter->getName() << std::endl;
			pIter = pIter->getNext();
		}
	}
	return os;
}