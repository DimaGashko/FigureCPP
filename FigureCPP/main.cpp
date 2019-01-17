#include <iostream>
#include <SFML/Graphics.hpp>

#include "Figure.hpp"

enum Keys {
	Left = sf::Keyboard::A,
	Top = sf::Keyboard::W,
	Right = sf::Keyboard::D,
	Bottom = sf::Keyboard::S,
	RotatePlus = sf::Keyboard::Right,
	RotateMinus = sf::Keyboard::Left,
	ScalePlus = sf::Keyboard::Up,
	ScaleMinus = sf::Keyboard::Down,
};

void controlFigure(Figure &figure, float frameTime);

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(1000, 600), "Figure", sf::Style::Default, settings);
	window.setFramerateLimit(180);

	Figure f1(sf::Vector2f(500, 300), 100, 0.2f);
	Figure f2(sf::Vector2f(100, 250), 35, 0.6f);
	Figure f3(sf::Vector2f(900, 350), 35, 0.05f);

	sf::Clock clock;
	float frameTime;

	while (window.isOpen()) {
		frameTime = (float)clock.restart().asMilliseconds();
		  
		sf::Event event; 
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::Resized) {
				sf::FloatRect visible(0, 0, float(event.size.width), float(event.size.height));
				window.setView(sf::View(visible));
			}
		}

		controlFigure(f1, frameTime);

		window.clear();
		f1.draw(window);
		f2.draw(window);
		f3.draw(window);
		window.display();
	}

	return 0;
}

void controlFigure(Figure &figure, float frameTime) {
	typedef sf::Keyboard::Key Key;

	float step = 0.3f * frameTime;
	float angle = 0.005f * frameTime;
	float scale = 0.05f * frameTime;

	if (sf::Keyboard::isKeyPressed((Key)Keys::Left)) {
		figure.move(sf::Vector2f(-step, 0));
	}
	if (sf::Keyboard::isKeyPressed((Key)Keys::Right)) {
		figure.move(sf::Vector2f(step, 0));
	}
	if (sf::Keyboard::isKeyPressed((Key)Keys::Top)) {
		figure.move(sf::Vector2f(0, -step));
	}
	if (sf::Keyboard::isKeyPressed((Key)Keys::Bottom)) {
		figure.move(sf::Vector2f(0, step));
	}

	if (sf::Keyboard::isKeyPressed((Key)Keys::ScalePlus)) {
		figure.setSize(figure.getSize() + scale);
	}
	if (sf::Keyboard::isKeyPressed((Key)Keys::ScaleMinus)) {
		figure.setSize(figure.getSize() - scale);
	}

	if (sf::Keyboard::isKeyPressed((Key)Keys::RotateMinus)) {
		figure.rotate(-angle);
	}
	if (sf::Keyboard::isKeyPressed((Key)Keys::RotatePlus)) {
		figure.rotate(angle);
	}
}