#ifndef UI_HPP_
#define UI_HPP_
#include <SFML/Graphics.hpp>
#include <memory>

class UI {
   public:
    UI();
    void UpdateHealthUI(double fraction, const std::string& text);
    void UpdateAbilityUI(double fraction, const std::string& text);
    void UpdateXpUI(double fraction, const std::string& text);
    void UpdateEndText(bool win);
    void draw(sf::RenderTarget& target) const;

   private:
    sf::RectangleShape healthBar_, abilityBar_, xpBar_;
    sf::RectangleShape healthBlackBar_, abilityBlackBar_, xpBlackBar_;
    sf::Text endText_, restartText_, healthInfoText_, abilityInfoText_, levelInfoText_;

    void Initialize();
};

#endif  // UI_HPP_
