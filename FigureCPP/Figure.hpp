#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>

class Figure {
public:
	Figure();
	Figure(sf::Vector2f coords, float angle = 0, float size = 20);
	void draw(sf::RenderWindow &window);
	void setPosition(sf::Vector2f coords);
	sf::Vector2f getPosition();
	void move(sf::Vector2f offset);
	void setAngle(float angle);
	float getAngle();
	void rotate(float angle);
	void setSize(float size);
	float getSize();
	void updatePoints();
	~Figure() {}

private:
	void drawFragment(sf::RenderWindow &window);

	void drawGeneralParts(sf::RenderWindow &window);

	sf::VertexArray _getBezierCoords(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, int count = 30);

	float _size;
	sf::Vector2f _coords;
	float _angle;

	sf::Vector2f _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9;

	static const double _BETA1;
	static const double _BETA2;
	static const double _P0P2;
	static const double _P0P8;

	static const double PI;
};