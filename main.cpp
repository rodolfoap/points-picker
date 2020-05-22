#include <iostream>
#include <fstream>
#include <tuple>
#include "window.h"
#include "form.h"

int main(int argc, char* argv[]) {
	if(argc<3) { std::cerr<<"Usage: "<<argv[0]<<" [IMAGE_FILE POINTS_FILE MUSTACHE_TEMPLATE]" <<std::endl; return 0; }
	sf::Event event;
	Form form(argv[2], argv[3]);
	Window window(1920, 1080, "PPicker", argv[1], form.cSize());

	// Loop
	form.message(window);
	while (window.isOpen()) {
		// Process events: waitEvent() is blocking, pollEvent() is not.
		while (window.waitEvent(event)) {
			if(event.type==sf::Event::Resized) { window.clear(); }
			if(event.type==sf::Event::MouseButtonPressed) {
				// Left click is adding point
				if(event.mouseButton.button==sf::Mouse::Left)  { window.addDot(sf::Mouse::getPosition(window)); }
				// Right click is removing last point
				if(event.mouseButton.button==sf::Mouse::Right) { window.removeDot(); }
				form.message(window);
			}
			// Close window or pressing Q
			if((event.key.code==sf::Keyboard::Q)||(event.type==sf::Event::Closed)) {
				if(form.render(window.dots)) window.close();
			}
			// Drawing
			window.drawBackground();
			window.drawDots();
			window.display();
		}
	}
	return EXIT_SUCCESS;
}
