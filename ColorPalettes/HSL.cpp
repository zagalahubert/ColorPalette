#include "HSL.h"

constexpr float PI = 3.14159265f;

HSL::HSL()
	: m_cacheImage(sf::Vector2u(0,0)), m_cacheSize(sf::Vector2u(0, 0)), m_L(0.5f)
{
}

void HSL::setL(float l)
{	
	if (l != m_L)
	{
		m_L = l;
		m_cacheSize = { 0,0 };
	}
}

void HSL::calculateHSLPaletteImage(sf::Vector2u size, sf::Color color)
{
	if (!(size == m_cacheSize))
	{ 
		m_cacheSize = size;
		m_cacheImage = sf::Image(size, color);

		const sf::Vector2f mid = { size.x / 2.0f, size.y / 2.0f };
		const float r = std::min(mid.x, mid.y);

		for (unsigned int y = 0; y < size.y; y++)
		{
			for (unsigned int x = 0; x < size.x; x++)
			{
				float dx = x - mid.x;
				float dy = y - mid.y;

				float dist = std::sqrt(pow(dx, 2.0) + pow(dy, 2.0));

				if (dist < r)
				{
					float alfa = std::atan2(-dy, dx) * 180.0f / PI;
					if (alfa < 0.0)
						alfa += 360.0;

					sf::Vector3f rgb = HSLtoRGB({ alfa, dist/r , m_L });
					m_cacheImage.setPixel({ x,y }, sf::Color(static_cast<uint8_t>(rgb.x), 
						static_cast<uint8_t>(rgb.y), static_cast<uint8_t>(rgb.z)));
				}
			}
		}

	}
}

sf::Vector3f HSL::HSLtoRGB(sf::Vector3f hsl)
{
	// h s l --- x y z

	float C = (1 - std::fabs(2 * hsl.z - 1)) * hsl.y;
	float X = C * (1 - static_cast<float>(std::fabs(std::fmod((hsl.x / 60.0), 2.0) - 1)));
	float m = hsl.z - C / 2.0;

	sf::Vector3f rgbPrim;

	if (hsl.x < 60.0)
		rgbPrim = { C, X, 0 };
	else if (hsl.x < 120.0)
		rgbPrim = { X, C, 0 };
	else if (hsl.x < 180.0)
		rgbPrim = { 0, C, X };
	else if (hsl.x < 240.0)
		rgbPrim = { 0, X, C };
	else if (hsl.x < 300.0)
		rgbPrim = { X, 0, C };
	else if (hsl.x < 360.0)
		rgbPrim = { C, 0, X };

	return { (rgbPrim.x + m) * 255, (rgbPrim.y + m) * 255, (rgbPrim.z + m) * 255 };
}
