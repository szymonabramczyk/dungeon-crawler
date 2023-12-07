#include "UI.hpp"

#include "Assets.hpp"

UI::UI() {
    Initialize();
}

void UI::UpdateHealthUI(double fraction, const std::string& text) {
    health_bar_.setSize(sf::Vector2f(fraction * 200.f, 15.f));
    health_info_text_.setString(text);
}
void UI::UpdateAbilityUI(double fraction, const std::string& text) {
    ability_bar_.setSize(sf::Vector2f(fraction * 200.f, 15.f));
    ability_info_text_.setString(text);
}
void UI::UpdateXpUI(double fraction, const std::string& text) {
    xp_bar_.setSize(sf::Vector2f(fraction * 200.f, 15.f));
    level_info_text_.setString(text);
}

void UI::UpdateEndText(bool win) {
    if (win) {
        end_text_.setPosition(sf::Vector2f(575, 384));
        end_text_.setString("Victory!");
    } else {
        end_text_.setPosition(sf::Vector2f(500, 384));
        end_text_.setString("Game Over!");
    }
}

void UI::Initialize() {
    health_black_bar_.setFillColor(sf::Color::Black);  // Set the initial color
    health_black_bar_.setSize(sf::Vector2f(205, 20.f));
    health_black_bar_.setPosition(30, 910);  // Adjust the position as needed

    health_bar_.setFillColor(sf::Color::Red);  // Set the initial color
    health_bar_.setSize(sf::Vector2f(200.f, 15.f));
    health_bar_.setPosition(30, 910);  // Adjust the position as needed

    ability_black_bar_.setFillColor(sf::Color::Black);  // Set the initial color
    ability_black_bar_.setSize(sf::Vector2f(205, 20.f));
    ability_black_bar_.setPosition(30, 950);  // Adjust the position as needed

    ability_bar_.setFillColor(sf::Color::Yellow);  // Set the initial color
    ability_bar_.setSize(sf::Vector2f(200.f, 15.f));
    ability_bar_.setPosition(30, 950);  // Adjust the position as needed

    xp_black_bar_.setFillColor(sf::Color::Black);  // Set the initial color
    xp_black_bar_.setSize(sf::Vector2f(205.f, 20.f));
    xp_black_bar_.setPosition(30, 990);  // Adjust the position as needed

    xp_bar_.setFillColor(sf::Color::Green);  // Set the initial color
    xp_bar_.setPosition(30, 990);            // Adjust the position as needed

    end_text_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
    end_text_.setCharacterSize(85);
    end_text_.setFillColor(sf::Color::White);

    health_info_text_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
    health_info_text_.setCharacterSize(10);
    health_info_text_.setFillColor(sf::Color::White);
    health_info_text_.setString("Health: 100/100");
    health_info_text_.setPosition(30, 890);

    ability_info_text_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
    ability_info_text_.setCharacterSize(10);
    ability_info_text_.setFillColor(sf::Color::White);
    ability_info_text_.setString("Ability: Ready");
    ability_info_text_.setPosition(30, 932);

    level_info_text_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
    level_info_text_.setCharacterSize(10);
    level_info_text_.setFillColor(sf::Color::White);
    level_info_text_.setString("Level: 0");
    level_info_text_.setPosition(30, 972);

    restart_text_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
    restart_text_.setCharacterSize(25);
    restart_text_.setFillColor(sf::Color::White);
    restart_text_.setPosition(sf::Vector2f(700, 530));
}

void UI::draw(sf::RenderTarget& target) const {
    target.draw(health_black_bar_);
    target.draw(health_bar_);
    target.draw(ability_black_bar_);
    target.draw(ability_bar_);
    target.draw(xp_black_bar_);
    target.draw(xp_bar_);
    target.draw(end_text_);
    target.draw(health_info_text_);
    target.draw(ability_info_text_);
    target.draw(level_info_text_);
    target.draw(restart_text_);
}
