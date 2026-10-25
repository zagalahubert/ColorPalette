#include "HSV.h"

constexpr float PI = 3.14159265f;

HSV::HSV()
	: m_cacheImage(sf::Vector2u(0, 0)), m_cacheSize(sf::Vector2u(0, 0)), m_V(0.5f)
{
}

void HSV::setV(float v)
{
	if (v != m_V)
	{
		m_V = v;
		m_cacheSize = { 0,0 };
	}
}

void HSV::calculateHSVPaletteImage(sf::Vector2u size, sf::Color color)
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

					sf::Vector3f rgb = HSVtoRGB({ alfa, dist / r , m_V });
					m_cacheImage.setPixel({ x,y }, sf::Color(static_cast<uint8_t>(rgb.x),
						static_cast<uint8_t>(rgb.y), static_cast<uint8_t>(rgb.z)));
				}
			}
		}

	}
}

sf::Vector3f HSV::HSVtoRGB(sf::Vector3f hsv)
{
	// h s v --- x y z

	float C = hsv.y * hsv.z;
	float X = C * (1 - static_cast<float>(std::fabs(std::fmod((hsv.x / 60.0), 2.0) - 1)));
	float m = hsv.z - C;

	sf::Vector3f rgbPrim;

	if (hsv.x < 60.0)
		rgbPrim = { C, X, 0 };
	else if (hsv.x < 120.0)
		rgbPrim = { X, C, 0 };
	else if (hsv.x < 180.0)
		rgbPrim = { 0, C, X };
	else if (hsv.x < 240.0)
		rgbPrim = { 0, X, C };
	else if (hsv.x < 300.0)
		rgbPrim = { X, 0, C };
	else if (hsv.x < 360.0)
		rgbPrim = { C, 0, X };

	return { (rgbPrim.x + m) * 255, (rgbPrim.y + m) * 255, (rgbPrim.z + m) * 255 };
}
