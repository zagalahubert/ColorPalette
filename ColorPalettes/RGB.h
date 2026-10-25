#pragma once
#include <SFML/Graphics.hpp>

class RGB
{
private:
	sf::Vector2u m_cacheSize;
	sf::Image m_cacheImage;
	float m_B;
public:
	RGB();
	void setB(float b);
	void calculateRGBPaletteImage(sf::Vector2u size, sf::Color color = sf::Color::White);
	inline const int getB() const { return m_B; }
	inline const sf::Image& getImage() const { return m_cacheImage; }
};

