#ifndef ASSETS_HPP_
#define ASSETS_HPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>

/*! \brief Class for Asset manipulation. 

A class that is responsible for loading, storing and providing easy access to assets. 
All the assets are stored in their respective maps, using a std::string as a key and 
an unique pointer to the asset. The usage of unique pointers ensures proper assets 
handling and correct integration with SFML way of managing assets.
*/
class Assets {
   public:
    /*! a method that loads all the assets with the specified names, it takes the parameter 
    path of the executable and based on that it finds the paths for all the assets with the 
    specified names */
    static void LoadAssets(const std::string& path,
                           const std::vector<std::string>& texture_names,
                           const std::vector<std::string>& font_names,
                           const std::vector<std::string>& sound_names);
    /*! a method that loads a sound with the specified name from the specified file_path
    if the asset fails to be loaded, the std::runtime_error is thrown */
    static void LoadSound(const std::string& name, const std::string& file_path);
    /*! a method that loads a font with the specified name from the specified file_path
    if the asset fails to be loaded, the std::runtime_error is thrown */
    static void LoadFont(const std::string& name, const std::string& file_path);
    /*! a method that loads a texture with the specified name from the specified file_path
    if the asset fails to be loaded, the std::runtime_error is thrown */
    static void LoadTexture(const std::string& name, const std::string& file_path);
    /*! a static map that stores pairs of strings and Textures, allows for easy access 
    to the Textures from other parts of the program */
    static std::map<std::string, std::unique_ptr<sf::Texture>> textures;
    /*! a static map that stores pairs of strings and Fonts, allows for easy access 
    to the Fonts from other parts of the program */
    static std::map<std::string, std::unique_ptr<sf::Font>> fonts;
    /*! a static map that stores pairs of strings and Sounds, allows for easy access 
    to the Sounds from other parts of the program */
    static std::map<std::string, std::unique_ptr<sf::Sound>> sounds;

   private:
    /*! a private static map that stores pairs of strings and SoundBuffers, that is needed 
    for the proper functioning of sounds map, as each Sound needs a SoundBuffer stored associated with it */
    static std::map<std::string, std::unique_ptr<sf::SoundBuffer>> sound_buffers_;
};

#endif  // ASSETS_HPP_