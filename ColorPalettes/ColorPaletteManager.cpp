#include "ColorPaletteManager.h"
#include <iostream>
#include <filesystem>
#include <iomanip>

static std::string formater(float v, int num = 3)
{
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(num) << v;
	return ss.str();
}

ColorPaletteManager::ColorPaletteManager(sf::Vector2u windowSize, const std::string& fontPath)
	: m_windowSize(windowSize), m_slider({100, 300}, {850, 50}), m_sliderValue(m_slider.getValue()),
	m_deltaTime(0.f)
{
	std::filesystem::path path = std::filesystem::current_path() / std::filesystem::path{ fontPath };

	if (m_font.openFromFile(path))
		std::cout << "Font loaded succesfully" << std::endl;
	else
		std::cerr << "Could not open font file: " << fontPath << std::endl;
}

void ColorPaletteManager::onUpdate(float deltaTime)
{
	m_deltaTime = deltaTime;
	m_slider.onUpdate();

	m_hsl.setL(m_sliderValue);
	m_hsv.setV(m_sliderValue);
	m_cmy.setY(m_sliderValue);
	m_rgb.setB(m_sliderValue * 255);

	m_hsl.calculateHSLPaletteImage({ 300, 300 });
	m_hslTexture = sf::Texture{ m_hsl.getImage() };

	m_hsv.calculateHSVPaletteImage({ 300, 300 });
	m_hsvTexture = sf::Texture{ m_hsv.getImage() };

	m_cmy.calculateCMYPaletteImage({ 300, 300 });
	m_cmyTexture = sf::Texture{ m_cmy.getImage() };

	m_rgb.calculateRGBPaletteImage({ 300, 300 });
	m_rgbTexture = sf::Texture{ m_rgb.getImage() };
}

void ColorPaletteManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// HSL palette
	sf::Sprite s(m_hslTexture);
	s.setPosition({ 50, 50 });
	target.draw(s);

	sf::Text text(m_font, "HSL", 15U);
	text.setFillColor(sf::Color::Black);
	text.setPosition({ 50,50 });
	target.draw(text);

	text.setPosition({ 300, 350 });
	text.setString("L = " + formater(m_hsl.getL()));
	target.draw(text);

	// HSV palette
	s.setTexture(m_hsvTexture);
	s.setPosition({ 400, 50 });
	target.draw(s);

	text.setString("HSV");
	text.setPosition({ 400,50 });
	target.draw(text);

	text.setPosition({ 650, 350 });
	text.setString("V = " + formater(m_hsv.getV()));
	target.draw(text);

	// CMY palette
	s.setTexture(m_cmyTexture);
	s.setPosition({ 50, 400 });
	target.draw(s);
	
	text.setString("CMY");
	text.setPosition({ 50,400 });
	target.draw(text);

	text.setPosition({ 300, 700 });
	text.setString("Y = " + std::to_string(m_cmy.getY()) + "%");
	target.draw(text);

	// RGB palette
	s.setTexture(m_rgbTexture);
	s.setPosition({ 400, 400 });
	target.draw(s);

	text.setString("RGB");
	text.setPosition({ 400, 400 });
	target.draw(text);

	text.setPosition({ 650, 700 });
	text.setString("B = " + std::to_string(m_rgb.getB()));
	target.draw(text);

	target.draw(m_slider);

	text.setPosition({ 850, 360 });
	text.setString("Time: " + formater(m_deltaTime) + "ms");
	target.draw(text);
}

void ColorPaletteManager::processEvent(std::optional<sf::Event> event)
{
	m_slider.processEvent(event);
}
