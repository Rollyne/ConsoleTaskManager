#pragma once
class User
{
private:
	int id;
	char username[20];
	char password[20];
	char firstName[20];
	char lastName[20];
	bool isAdmin;
public:
	User();
	~User();

	void setId(int id);
	int getId();

	void setUsername(char username[20]);
	char* getUsername();

	void setPassword(char password[20]);
	char* getPassword();

	void setFirstName(char firstName[20]);
	char* getFirstName();

	void setLastName(char lastName[20]);
	char* getLastName();

	void setIsAdmin(bool isAdmin);
	bool getIsAdmin();

};

