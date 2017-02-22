#pragma once
#include "User.h"
#include "BaseRepository.cpp"

class UserRepository : public BaseRepository<User>
{
protected:
	void writeItem(User* item, std::ofstream* file) override;
	User* readItem(std::ifstream* file) override;
public:
	User* GetByUsernameAndPassword(char username[20], char password[20]);
	explicit UserRepository(char filepath[50]) : BaseRepository<User>(filepath) {}
};

