#include <SFML/Graphics.hpp>
#include <cmath>

#include "Figure.hpp"

Figure::Figure() :
	_coords(sf::Vector2f(0, 0)),
	_size(10),
	_angle(0)
{

}

Figure::Figure(sf::Vector2f coords, float size, float angle) :
	_coords(coords),
	_size(size),
	_angle(angle)
{

}

void Figure::draw(sf::RenderWindow &window) {
	const float angle = float(PI / 2);
	const float startAngle = _angle;

	for (int i = 0; i < 4; i++) {
		updatePoints();
		drawFragment(window);
		rotate(angle);
	}

	setAngle(startAngle);

	drawGeneralParts(window);
}

void Figure::drawFragment(sf::RenderWindow &window) {
	sf::Vertex part1[] = { _p1, _p2, _p3, _coords };
	sf::Vertex part2[] = { _coords, _p4 };
	sf::Vertex part3[] = { _p5, _p6, _p7 };

	auto arc1 = _getBezierCoords(_coords, _p8, _p4, 15);
	auto arc2 = _getBezierCoords(_coords, _p9, _p4, 15);

	window.draw(part1, 4, sf::LineStrip);
	window.draw(part2, 2, sf::Lines);
	window.draw(part3, 3, sf::LineStrip);
	window.draw(arc1);
	window.draw(arc2);
}

void Figure::drawGeneralParts(sf::RenderWindow &window) {
	sf::CircleShape circle(_size);
	circle.setOrigin(_size, _size);
	circle.setPosition(_coords);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(1);

	window.draw(circle);
}

void Figure::updatePoints() {
	_p1.x = float(_coords.x + _size * cos(_angle + PI / 2) * 8 / 3);
	_p1.y = float(_coords.y + _size * sin(_angle + PI / 2) * 8 / 3);

	_p2.x = float(_coords.x + _P0P2 * _size * cos(_angle + _BETA1));
	_p2.y = float(_coords.y + _P0P2 * _size * sin(_angle + _BETA1));

	_p3.x = float(_coords.x + 2 * _size * cos(_angle + PI / 2)),
		_p3.y = float(_coords.y + 2 * _size * sin(_angle + PI / 2));

	_p4.x = float(_coords.x + 2 * _size * cos(_angle + PI / 4));
	_p4.y = float(_coords.y + 2 * _size * sin(_angle + PI / 4));

	_p5.x = float(_coords.x + 2 * _size * cos(_angle));
	_p5.y = float(_coords.y + 2 * _size * sin(_angle));

	_p6.x = float(_coords.x + _P0P2 * _size * cos(_angle + _BETA2));
	_p6.y = float(_coords.y + _P0P2 * _size * sin(_angle + _BETA2));

	_p7.x = float(_coords.x + _size * cos(_angle) * 8 / 3);
	_p7.y = float(_coords.y + _size * sin(_angle) * 8 / 3);

	_p8.x = float(_coords.x + _P0P8 * _size * cos(_angle + PI / 2));
	_p8.y = float(_coords.y + _P0P8 * _size * sin(_angle + PI / 2));

	_p9.x = float(_coords.x + _P0P8 * _size * cos(_angle));
	_p9.y = float(_coords.y + _P0P8 * _size * sin(_angle));
}

void Figure::setPosition(sf::Vector2f coords) {
	_coords.x = coords.x;
	_coords.y = coords.y;
}

sf::Vector2f Figure::getPosition() {
	return sf::Vector2f(_coords);
}

void Figure::move(sf::Vector2f offset) {
	setPosition(_coords + offset);
}

void Figure::setAngle(float angle) {
	_angle = angle;
}

float Figure::getAngle() {
	return _angle;
}

void Figure::rotate(float angle) {
	setAngle(_angle + angle);
}

void Figure::setSize(float size) {
	if (size < 1) size = 1;
	_size = size;
}

float Figure::getSize() {
	return _size;
}

sf::VertexArray Figure::_getBezierCoords(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, int count) {
	if (count < 3) count = 3;

	sf::VertexArray vertices(sf::LineStrip, count);

	for (int i = 0; i < count; i++) {
		float t = float(i) / (count - 1);

		vertices[i].position = ((1.f - t) * (1.f - t)) * p1
			+ (2.f * (1.f - t) * t) * p2
			+ (t * t) * p3;
	}

	return vertices;
}

const double Figure::PI = 3.14159265358979323846;

const double Figure::_BETA1 = atan(7);
const double Figure::_BETA2 = PI / 2 - Figure::_BETA1;
const double Figure::_P0P2 = 1.f / 3.f * sqrt(50);
const double Figure::_P0P8 = sqrt(2);


