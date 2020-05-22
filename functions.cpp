#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#define LOG std::cerr<<">>> "<<__FILE__<<"["<<__LINE__<<"]:"<<__func__<<"();"<<std::endl;
std::vector<std::tuple<float, float, std::string>> readPoints(std::string name){
	std::vector<std::tuple<float, float, std::string>> coords;
	float a, b; std::string c;
	std::ifstream ifs(name, std::ios::binary);
	while(ifs>>a>>b>>c) coords.push_back(make_tuple(a, b, c));
	ifs.close();
	return coords;
}
std::string readFile(std::string name){
	std::ifstream ifs(name, std::ios::binary);
	std::stringstream buffer;
	buffer<<ifs.rdbuf();
	ifs.close();
	return buffer.str();
}
