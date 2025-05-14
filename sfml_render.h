
//sfml_render.h

#pragma once

#include <SFML/Graphics.hpp>
#include "frog_model.h"  
#include <unordered_map>

class SFMLRenderer {
private:
                              // Окно SFML
    const model& game_model;   
    sf::RenderWindow window;   
    sf::Texture player_texture; 
    sf::Texture tree_texture;
    sf::Texture swamp_texture;
    sf::Texture background_texture;
    sf::Font font;

    sf::Sprite player_sprite; 
    sf::Sprite background_sprite;    

    std::unordered_map<objects, sf::Texture> object_textures;


    void createFallbackTexture(sf::Texture& texture, sf::Color color);
    void load_resources();
    void handle_events();         // Обработка событий ввода
    void render();                // Отрисовка кадра

public:
    
    SFMLRenderer(const model& m);
    
    void run();
};
