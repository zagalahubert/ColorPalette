#pragma once
#include <SFML/Graphics.hpp>

class HSL
{
private:
	sf::Vector2u m_cacheSize;
	sf::Image m_cacheImage;
	float m_L;
public:
	HSL();
	void setL(float l);
	void calculateHSLPaletteImage(sf::Vector2u size, sf::Color color = sf::Color::White);
	sf::Vector3f HSLtoRGB(sf::Vector3f hsl);
	inline const float getL() const { return m_L; }
	inline const sf::Image& getImage() const { return m_cacheImage; }
};

