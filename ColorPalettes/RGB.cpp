#include "RGB.h"

constexpr float PI = 3.14159265f;

RGB::RGB()
	: m_cacheImage(sf::Vector2u(0, 0)), m_cacheSize(sf::Vector2u(0, 0)), m_B(150.f)
{
}

void RGB::setB(float b)
{
	if (b != m_B)
	{
		m_B = b;
		m_cacheSize = { 0,0 };
	}
}

void RGB::calculateRGBPaletteImage(sf::Vector2u size, sf::Color color)
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

					sf::Vector3f rgb = { 255.f * dist / r, 255.f * alfa / 360.f, m_B };
					m_cacheImage.setPixel({ x,y }, sf::Color(static_cast<uint8_t>(rgb.x),
						static_cast<uint8_t>(rgb.y), static_cast<uint8_t>(rgb.z)));
				}
			}
		}

	}
}
