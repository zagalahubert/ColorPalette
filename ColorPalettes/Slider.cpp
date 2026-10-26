#include "Slider.h"

#include <iostream>
void Slider::calculateLinePosition()
{
    m_selectedLinePosition.x = m_sliderPosition.x;

    float y = m_cursorPosition.y;

    if (y < m_sliderPosition.y)
        m_selectedLinePosition.y = m_sliderPosition.y;
    else if (m_sliderPosition.y + m_sliderSize.y < y)
        m_selectedLinePosition.y = m_sliderPosition.y + m_sliderSize.y;
    else
        m_selectedLinePosition.y = m_cursorPosition.y;

    m_selectedLinePosition.y -= m_selectedLineSize.y / 2.0f;
}

Slider::Slider(sf::Vector2u sliderSize, sf::Vector2u sliderPosition)
    : m_sliderSize({ static_cast<float>(sliderSize.x), static_cast<float>(sliderSize.y) }), 
    m_sliderPosition({ static_cast<float>(sliderPosition.x), static_cast<float>(sliderPosition.y) }), 
    m_slideArea(sf::PrimitiveType::TriangleStrip, 4), m_clicked(false), m_value(0.5f), 
    m_selectedLinePosition{ 0, 0 }, m_cursorPosition({ 100, static_cast<int>(m_sliderPosition.y + m_sliderSize.y / 2) }),
    m_selectedLineSize({ static_cast<float>(sliderSize.x), sliderSize.y * 0.035f}), m_selectedLine(m_selectedLineSize)
{
    m_padding = { m_sliderSize.x * 0.15f, m_sliderSize.y };
    m_slideAreaSize = { m_sliderSize.x - 2 * m_padding.x, m_sliderSize.y };
    m_slideAreaBorder.setSize({ m_slideAreaSize.x, m_slideAreaSize.y });
    m_slideAreaBorder.setFillColor(sf::Color::Transparent);
    m_slideAreaBorder.setOutlineColor(sf::Color::Black);
    m_slideAreaBorder.setOutlineThickness(5.f);

    //Slide area setup
    sf::Vector2f m_slideAreaPosition = { m_sliderPosition.x + m_padding.x, m_sliderPosition.y };
    m_slideArea[0].position = m_slideAreaPosition;
    m_slideArea[0].color = sf::Color::Black;
    m_slideArea[1].position = { m_slideAreaPosition.x + m_slideAreaSize.x, m_slideAreaPosition.y };
    m_slideArea[1].color = sf::Color::Black;
    m_slideArea[2].position = { m_slideAreaPosition.x, m_slideAreaPosition.y + m_slideAreaSize.y };
    m_slideArea[2].color = sf::Color::White;
    m_slideArea[3].position = { m_slideAreaPosition.x + m_slideAreaSize.x, m_slideAreaPosition.y + m_slideAreaSize.y };
    m_slideArea[3].color = sf::Color::White;

    m_slideAreaBorder.setPosition({ m_slideAreaPosition });
    
    calculateLinePosition();
    m_selectedLine.setFillColor(sf::Color::Black);
    m_selectedLine.setPosition(m_selectedLinePosition);
}

void Slider::processEvent(std::optional<sf::Event> event)
{
    if (const sf::Event::MouseButtonPressed* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
        {
            m_clicked = true;
            m_cursorPosition = mouseButtonPressed->position;
        }
    }
    
    if (const sf::Event::MouseMoved* mouseButtonMoved = event->getIf<sf::Event::MouseMoved>())
    {
        if (m_clicked)
        {
            m_cursorPosition = mouseButtonMoved->position;
        }
    }

    if (const sf::Event::MouseButtonReleased* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
    {
        if (mouseButtonReleased->button == sf::Mouse::Button::Left)
        {
            m_clicked = false;
        }
    }
}

void Slider::onUpdate()
{   
    if (!m_clicked)
        return;

    calculateLinePosition();
    m_selectedLine.setPosition(m_selectedLinePosition);
    
    m_value =  (m_selectedLinePosition.y - m_sliderPosition.y + m_selectedLineSize.y / 2.0f) / m_sliderSize.y;
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(m_slideArea);
    target.draw(m_slideAreaBorder);
    target.draw(m_selectedLine);
}
