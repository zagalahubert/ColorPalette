#pragma once
#include <SFML/Graphics.hpp>

class CMY
{
private:
	sf::Vector2u m_cacheSize;
	sf::Image m_cacheImage;
	float m_Y;
public:
	CMY();
	void setY(float y);
	void calculateCMYPaletteImage(sf::Vector2u size, sf::Color color = sf::Color::White);
	sf::Vector3f CMYtoRGB(sf::Vector3f cmy);
	inline const float getY() const { return m_Y * 100; }
	inline const sf::Image& getImage() const { return m_cacheImage; }
};

