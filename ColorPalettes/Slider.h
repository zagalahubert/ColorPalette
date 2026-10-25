#pragma once
#include <SFML/Graphics.hpp>

class Slider : public sf::Drawable
{
private:
	void calculateLinePosition();
public:
	Slider(sf::Vector2u sliderSize, sf::Vector2u sliderPosition);
	void processEvent(std::optional<sf::Event> event);
	void onUpdate();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	inline const float& getValue() const { return m_value; }
private:
	sf::Vector2f m_sliderSize, m_sliderPosition, m_padding, m_slideAreaSize, m_slideAreaPosition, m_selectedLinePosition, m_selectedLineSize;
	sf::Vector2i m_cursorPosition;
	sf::VertexArray m_slideArea;
	sf::RectangleShape m_slideAreaBorder, m_selectedLine;
	float m_value;
	bool m_clicked;
};

