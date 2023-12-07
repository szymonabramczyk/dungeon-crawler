#ifndef ASSETS_HPP_
#define ASSETS_HPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>

class Assets {
   public:
    static void LoadAssets(const std::string& path,
                           const std::vector<std::string>& texture_names,
                           const std::vector<std::string>& font_names,
                           const std::vector<std::string>& sound_names);
    static void LoadSound(const std::string& name, const std::string& file_path);
    static void LoadFont(const std::string& name, const std::string& file_path);
    static void LoadTexture(const std::string& name, const std::string& file_path);
    static std::map<std::string, std::unique_ptr<sf::Texture>> textures;
    static std::map<std::string, std::unique_ptr<sf::Font>> fonts;
    static std::map<std::string, std::unique_ptr<sf::Sound>> sounds;

   private:
    static std::map<std::string, std::unique_ptr<sf::SoundBuffer>> sound_buffers_;
};

#endif  // ASSETS_HPP_