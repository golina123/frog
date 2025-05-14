//sfml_render.cpp

#include "sfml_render.h"
#include <iostream>
#include <filesystem>

SFMLRenderer::SFMLRenderer(const model& m) : 
    game_model(m),
    window(sf::VideoMode(800, 600), "Frog Game SFML") 
{



    // Загрузка текстуры
    if (!player_texture.loadFromFile("assets/player.png")) 
    {
        std::cerr << "Error loading texture! Using fallback.\n";
	createFallbackTexture(player_texture, sf::Color::Red);
    }

    if (!tree_texture.loadFromFile("assets/tree.png"))
    {
        std::cerr << "Error loading tree texture! Using fallback.\n";
        createFallbackTexture(tree_texture, sf::Color::Green);
    }
    
    if (!swamp_texture.loadFromFile("assets/swamp.png"))
    {
        std::cerr << "Error loading swamp texture! Using fallback.\n";
        createFallbackTexture(swamp_texture, sf::Color::Blue);
    }
   if (!swamp_texture.loadFromFile("assets/swamp.png")) {
 	   std::cerr << "Error loading swamp texture! Using fallback.\n";
    	createFallbackTexture(swamp_texture, sf::Color::Blue);
	}
   else {
    	      std::cout << "Swamp texture loaded successfully. Size: " 
              << swamp_texture.getSize().x << "x" 
              << swamp_texture.getSize().y << std::endl;
	}

   if (!background_texture.loadFromFile("assets/background.png"))
   {
        std::cerr << "Error loading background texture! Using fallback.\n";
        createFallbackTexture(background_texture, sf::Color(100, 100, 100)); // Серый фон
    }

    player_sprite.setTexture(player_texture);
    background_sprite.setTexture(background_texture);

    float cell_size = 64.f; // Размер клетки в пикселях
    player_sprite.setScale(
        cell_size / player_texture.getSize().x,
        cell_size / player_texture.getSize().y
    );
}

void SFMLRenderer::createFallbackTexture(sf::Texture& texture, sf::Color color) {
    sf::Uint8 pixels[32*32*4];
    for (int i = 0; i < 32*32*4; i += 4) {
        pixels[i]   = color.r;   
        pixels[i+1] = color.g;   
        pixels[i+2] = color.b;   
        pixels[i+3] = 255;      
    }
    texture.create(32, 32);
    texture.update(pixels);
}


// Главный цикл
void SFMLRenderer::run() {
    while (window.isOpen()) {
        handle_events();
        render();
        sf::sleep(sf::milliseconds(16)); 
    }
}


void SFMLRenderer::handle_events() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        if (event.type == sf::Event::KeyPressed)
       	{
	    model& mutable_model = const_cast<model&>(game_model);
            switch (event.key.code) {
                case sf::Keyboard::W: mutable_model.process_action(MOVE_UP); break;
                case sf::Keyboard::S: mutable_model.process_action(MOVE_DOWN); break;
                case sf::Keyboard::A: mutable_model.process_action(MOVE_LEFT); break;
                case sf::Keyboard::D: mutable_model.process_action(MOVE_RIGHT); break;
                case sf::Keyboard::T: mutable_model.process_action(TREE); break;
                case sf::Keyboard::Q: window.close(); break;
		default: break;
            }
        }
    }
}

// Отрисовка
void SFMLRenderer::render() {
    window.clear();
    window.draw(background_sprite);

    const int screen_width = game_model.get_screen_width();
    const int screen_height = game_model.get_screen_height();
    
    // Рисуем игрока
    auto player_pos = game_model.get_player_pos();
    
    player_sprite.setPosition(player_pos.first * 64, player_pos.second * 64);
    window.draw(player_sprite);
    
    for (const auto& tree : game_model.get_trees())
    {
        sf::Sprite tree_sprite(tree_texture);
        auto pos = tree.get_pos();
        tree_sprite.setPosition(pos.first * 64, pos.second * 64);
        tree_sprite.setScale(
            64.f / tree_texture.getSize().x,
            64.f / tree_texture.getSize().y
        );
        window.draw(tree_sprite);
    }

    std::cout << "Rendering " << game_model.get_swamp().size() << " swamp tiles\n";

    for (const auto& swamp : game_model.get_swamp()) {
        auto pos = swamp.get_pos();

        if (pos.first < 0 || pos.second < 0 ||  pos.first >= screen_width || pos.second >= screen_height) {
		std::cerr << "Swamp at invalid position: " << pos.first << "," << pos.second << std::endl;
        continue;
        }

	float x = pos.first * 64.f;
        float y = pos.second * 64.f ;

    	if (x >= 800 || y >= 600) {
	        std::cerr << "Swamp at invalid pixel position: " 
                  << x << "," << y << std::endl;
        	continue;
    	}


	 sf::Sprite swamp_sprite(swamp_texture);
   	 swamp_sprite.setPosition(x, y);
    
   
    if (swamp_texture.getSize().x > 0 && swamp_texture.getSize().y > 0) {
        swamp_sprite.setScale(
            64.f / swamp_texture.getSize().x,
            64.f / swamp_texture.getSize().y
        );
    }
    
    window.draw(swamp_sprite);
    std::cout << "Successfully drawn swamp at: " << pos.first << ", " << pos.second << std::endl;
}
	

    window.display();
}
