#ifndef UI_HPP_
#define UI_HPP_
#include <memory>

#include <SFML/Graphics.hpp>

class UI {
    public:
        UI();
        void updateHealthUI(double fraction, const std::string& text);
        void updateAbilityUI(double fraction, const std::string& text);
        void updateXpUI(double fraction, const std::string& text);
        void updateEndText(bool win);
        void draw(sf::RenderTarget& target) const;

    private:
        sf::RectangleShape healthBar_, abilityBar_, xpBar_;
        sf::RectangleShape healthBlackBar_, abilityBlackBar_, xpBlackBar_;
        sf::Text endText_, restartText_, healthInfoText_, abilityInfoText_, levelInfoText_;
        
        void initialize();
};

#endif // UI_HPP_
