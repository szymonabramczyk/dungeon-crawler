#ifndef UI_HPP_
#define UI_HPP_
#include <SFML/Graphics.hpp>

/*! \brief Represents the player UI. */
class UI {
   public:
    UI();
    void UpdateHealthUI(double fraction, const std::string& text);
    void UpdateAbilityUI(double fraction, const std::string& text);
    void UpdateXpUI(double fraction, const std::string& text);
    void UpdateEndText(bool win);
    void draw(sf::RenderTarget& target) const;

   private:
    sf::RectangleShape health_bar_, ability_bar_, xp_bar_;
    sf::RectangleShape health_black_bar_, ability_black_bar_, xp_black_bar_;
    sf::Text end_text_, restart_text_, health_info_text_, ability_info_text_, level_info_text_;

    void Initialize();
};

#endif  // UI_HPP_
