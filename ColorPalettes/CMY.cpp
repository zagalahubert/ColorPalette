#include "CMY.h"

constexpr float PI = 3.14159265f;

CMY::CMY()
	: m_cacheImage(sf::Vector2u(0, 0)), m_cacheSize(sf::Vector2u(0, 0)), m_Y(0.54f)
{
}

void CMY::setY(float y)
{
	if (y != m_Y)
	{
		m_Y = y;
		m_cacheSize = { 0,0 };
	}
}

void CMY::calculateCMYPaletteImage(sf::Vector2u size, sf::Color color)
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

					sf::Vector3f rgb = CMYtoRGB({ alfa / 360.f, dist / r, m_Y });
					m_cacheImage.setPixel({ x,y }, sf::Color(static_cast<uint8_t>(rgb.x),
						static_cast<uint8_t>(rgb.y), static_cast<uint8_t>(rgb.z)));
				}
			}
		}

	}
}

sf::Vector3f CMY::CMYtoRGB(sf::Vector3f cmy)
{
	// c m y --- x y z

	return {255.f * (1 - cmy.x), 255.f * (1 - cmy.y), 255.f * (1 - cmy.z) };
}
