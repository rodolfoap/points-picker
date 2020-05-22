#include <string>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "window.h"
#include "functions.cpp"
#include "mustache.hpp"
#include "form.h"
Form::Form(char* pFile, char* tFile):
	coorduv(kainjow::mustache::data::type::list),
	coordxy(kainjow::mustache::data::type::list),
	pFile(pFile), tFile(tFile) {
	coords=readPoints(pFile);
}
void Form::adduv(float x, float y, bool last) {
	kainjow::mustache::data pair;
	pair.set("x", std::to_string(x));
	pair.set("y", std::to_string(y));
	pair.set("last", last);
	coorduv<<kainjow::mustache::data{pair};
}
void Form::addxy(float x, float y, std::string c, bool last) {
	kainjow::mustache::data pair;
	pair.set("x", std::to_string(x));
	pair.set("y", std::to_string(y));
	pair.set("c", c);
	pair.set("last", last);
	coordxy<<kainjow::mustache::data{pair};
}
void Form::message(Window& window) {
	int i=window.dots.size();
	std::string msg;
	if(i<coords.size())  msg="Select point: "+std::get<2>(coords[i]);
	if(i==coords.size()) msg="[DONE] Push Q to end and generate matrix.";
	if(i>coords.size())  msg="[ERROR] No more points. Roll back with mouse::RIGHT-CLICK.";
	std::cerr<<msg<<std::endl;
	window.setTitle(msg);
}
int Form::cSize() {
	return coords.size();
}
bool Form::render(std::vector<sf::Vector2f> dots) {
	if(coords.size()!=dots.size()) {
		std::cerr<<"[ERROR] The number of expected("<<coords.size()<<") and provided points ("<<dots.size()<<") is different."<<std::endl;
		return false;
	}
	for(int i=0; i<coords.size(); i++) addxy(std::get<0>(coords[i]), std::get<1>(coords[i]), std::get<2>(coords[i]), (i+1==coords.size()));
	for(int i=0; i<dots.size(); i++) adduv(dots[i].x, dots[i].y, (i+1==coords.size()));
	data.set("rows", std::to_string(dots.size()));
	data.set("coorduv", coorduv);
	data.set("coordxy", coordxy);
	kainjow::mustache::mustache tpl{readFile(tFile)};
	std::cerr<<std::endl<<tpl.render(data)<<std::endl;

	// Generate yaml file
	std::ofstream yaml;
	yaml.open ("points_matrix.yaml");
	yaml<<tpl.render(data);
	yaml.close();
	return true;
}
