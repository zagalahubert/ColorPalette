#pragma once
#include <SFML/Graphics.hpp>

class HSV
{
private:
	sf::Vector2u m_cacheSize;
	sf::Image m_cacheImage;
	float m_V;
public:
	HSV();
	void setV(float v);
	void calculateHSVPaletteImage(sf::Vector2u size, sf::Color color = sf::Color::White);
	sf::Vector3f HSVtoRGB(sf::Vector3f hsv);
	inline const float getV() const { return m_V; }
	inline const sf::Image& getImage() const { return m_cacheImage; }
};

