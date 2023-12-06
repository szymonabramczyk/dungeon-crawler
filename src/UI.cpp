#include "UI.hpp"
#include "Assets.hpp"

UI::UI() {
    initialize();
}

void UI::updateHealthUI(double fraction, const std::string& text) {
    healthBar_.setSize(sf::Vector2f(fraction * 200.f, 15.f));
    healthInfoText_.setString(text);
}
void UI::updateAbilityUI(double fraction, const std::string& text) {
    abilityBar_.setSize(sf::Vector2f(fraction * 200.f, 15.f));
    abilityInfoText_.setString(text);
}
void UI::updateXpUI(double fraction, const std::string& text) {
    xpBar_.setSize(sf::Vector2f(fraction * 200.f, 15.f));
    levelInfoText_.setString(text);
}

void UI::updateEndText(bool win) {
    if (win) {
        endText_.setPosition(sf::Vector2f(575, 384));
        endText_.setString("Victory!");
    } else {
        endText_.setPosition(sf::Vector2f(500, 384));
        endText_.setString("Game Over!");
    }
}

void UI::initialize() {
    healthBlackBar_.setFillColor(sf::Color::Black); // Set the initial color
    healthBlackBar_.setSize(sf::Vector2f(205, 20.f));
    healthBlackBar_.setPosition(30, 910); // Adjust the position as needed

    healthBar_.setFillColor(sf::Color::Red); // Set the initial color
    healthBar_.setSize(sf::Vector2f(200.f, 15.f));
    healthBar_.setPosition(30, 910); // Adjust the position as needed

    abilityBlackBar_.setFillColor(sf::Color::Black); // Set the initial color
    abilityBlackBar_.setSize(sf::Vector2f(205, 20.f));
    abilityBlackBar_.setPosition(30, 950); // Adjust the position as needed

    abilityBar_.setFillColor(sf::Color::Yellow); // Set the initial color
    abilityBar_.setSize(sf::Vector2f(200.f, 15.f));
    abilityBar_.setPosition(30, 950); // Adjust the position as needed

    xpBlackBar_.setFillColor(sf::Color::Black); // Set the initial color
    xpBlackBar_.setSize(sf::Vector2f(205.f, 20.f));
    xpBlackBar_.setPosition(30, 990); // Adjust the position as needed

    xpBar_.setFillColor(sf::Color::Green); // Set the initial color
    xpBar_.setPosition(30, 990); // Adjust the position as needed

    endText_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
    endText_.setCharacterSize(85);
    endText_.setFillColor(sf::Color::White);

    healthInfoText_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
    healthInfoText_.setCharacterSize(10);
    healthInfoText_.setFillColor(sf::Color::White);
    healthInfoText_.setString("Health: 100/100");
    healthInfoText_.setPosition(30, 890);

    abilityInfoText_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
    abilityInfoText_.setCharacterSize(10);
    abilityInfoText_.setFillColor(sf::Color::White);
    abilityInfoText_.setString("Ability: Ready");
    abilityInfoText_.setPosition(30, 932);

    levelInfoText_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
    levelInfoText_.setCharacterSize(10);
    levelInfoText_.setFillColor(sf::Color::White);
    levelInfoText_.setString("Level: 0");
    levelInfoText_.setPosition(30, 972);

    restartText_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
    restartText_.setCharacterSize(25);
    restartText_.setFillColor(sf::Color::White);
    restartText_.setPosition(sf::Vector2f(700, 530));
}

void UI::draw(sf::RenderTarget& target) const {
    target.draw(healthBlackBar_); 
    target.draw(healthBar_); 
    target.draw(abilityBlackBar_); 
    target.draw(abilityBar_); 
    target.draw(xpBlackBar_); 
    target.draw(xpBar_); 
    target.draw(endText_); 
    target.draw(healthInfoText_); 
    target.draw(abilityInfoText_); 
    target.draw(levelInfoText_); 
    target.draw(restartText_); 
}
    