#include <iostream>
#include <SFML/Graphics.hpp>
#include "window.h"
#define RADIUS 4

Window::Window(const int width, const int height, const std::string title, const char* bgndfile, int cSize):
	sf::RenderWindow(sf::VideoMode(width, height), title), dot(RADIUS), cSize(cSize){

	// Background
	texture.loadFromFile(bgndfile);
	this->setSize(texture.getSize());
	background.setTexture(texture);
	// Dot
	dot.setFillColor(sf::Color(255, 0, 0));
	// Screen setup
	this->clear();
	this->draw(background);
	this->display();
}
void Window::drawBackground(){
	this->clear();
	this->draw(background);
};
void Window::addDot(sf::Vector2i pixelPos){
	if(dots.size()<cSize) { 
		// See https://www.sfml-dev.org/tutorials/2.0/graphics-view.php#showing-more-when-the-window-is-resized
		sf::Vector2f worldPos=this->mapPixelToCoords(pixelPos);
		dots.push_back(worldPos);
	}
	else {
		std::cerr<<"[ERROR] Cannot add more points."<<std::endl;
	}
}
void Window::removeDot(){
	if(dots.size()>0) dots.pop_back();
}
void Window::drawDots(){
	for(int i=0; i<dots.size(); i++) {
		dot.setPosition(dots[i].x-RADIUS-1, dots[i].y-RADIUS-1);
		this->draw(dot);
	}
}
