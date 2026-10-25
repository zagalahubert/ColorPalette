#pragma once
#include <SFML/Graphics.hpp>

#include "HSL.h"
#include "RGB.h"
#include "CMY.h"
#include "HSV.h"
#include "Slider.h"

class ColorPaletteManager : public sf::Drawable
{
private:

public:
	ColorPaletteManager(sf::Vector2u windowSize, const std::string& fontPath);
	void onUpdate(float deltaTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void processEvent(std::optional<sf::Event> event);
private:
	HSL m_hsl; HSV m_hsv; CMY m_cmy; RGB m_rgb;
	sf::Texture m_hslTexture, m_hsvTexture, m_cmyTexture, m_rgbTexture;
	Slider m_slider;
	sf::Vector2u m_windowSize;
	sf::Font m_font;
	const float& m_sliderValue;
	float m_deltaTime;
};

