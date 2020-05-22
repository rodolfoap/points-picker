#include "mustache.hpp"
class Form{
private:
	kainjow::mustache::data data;
	kainjow::mustache::data coorduv;
	kainjow::mustache::data coordxy;
	std::string pFile;
	std::string tFile;
	std::vector<std::tuple<float, float, std::string>> coords;
public:
	Form(char*, char*);
	void adduv(float, float, bool);
	void addxy(float, float, std::string, bool);
	bool render(std::vector<sf::Vector2f>);
	void message(Window&);
	int cSize();
};
