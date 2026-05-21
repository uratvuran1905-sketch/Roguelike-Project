#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Pencere ayari
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dungeon Crawler - Murat Vuran");
    window.setFramerateLimit(60); 

    // --- ZEMIN (FLOOR) GORSELLIGI ---
    sf::Texture floorTexture;
    // assets klasorunun dogru yolu
    if (!floorTexture.loadFromFile("../../assets/floor.png")) {
        std::cout << "HATA: floor.png bulunamadi!" << std::endl;
    }
    sf::Sprite floorSprite;
    floorSprite.setTexture(floorTexture);

    // --- KARAKTER (PLAYER) GORSELLIGI ---
    sf::Texture playerTexture;
    // assets klasorunun dogru yolu
    if (!playerTexture.loadFromFile("../../assets/player.png")) {
        std::cout << "HATA: player.png bulunamadi!" << std::endl;
    }
    sf::Sprite player;
    player.setTexture(playerTexture);
    
    // Karakterin boyutunu ve baslangic konumunu ayarla
    player.setScale(0.5f, 0.5f); 
    player.setPosition(380.f, 280.f); 

    float moveSpeed = 5.0f;

    // --- OYUN DONGUSU ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // --- HAREKET KONTROLLERİ (WASD) ---
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.move(0.f, -moveSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.move(0.f, moveSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.move(-moveSpeed, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.move(moveSpeed, 0.f);

        // --- SINIR KONTROLLERİ ---
        sf::Vector2f pos = player.getPosition();
        float playerWidth = player.getGlobalBounds().width;
        float playerHeight = player.getGlobalBounds().height;

        if (pos.x < 0.f) pos.x = 0.f;
        if (pos.x > 800.f - playerWidth) pos.x = 800.f - playerWidth;
        if (pos.y < 0.f) pos.y = 0.f;
        if (pos.y > 600.f - playerHeight) pos.y = 600.f - playerHeight;

        player.setPosition(pos);

        // --- CIZIM ASAMASI ---
        window.clear(sf::Color::Black);
        
        // 1. Zemini Ciz (Doseme Mantigi)
        float tileW = floorSprite.getGlobalBounds().width;
        float tileH = floorSprite.getGlobalBounds().height;

        // Eger resim yuklenmisse ve boyutlari 0'dan buyukse ekrani kapla
        if (tileW > 0 && tileH > 0) {
            for (float x = 0; x < 800; x += tileW) {
                for (float y = 0; y < 600; y += tileH) {
                    floorSprite.setPosition(x, y);
                    window.draw(floorSprite); 
                }
            }
        }

        // 2. Karakteri Ciz (Zeminin ustunde kalmasi icin sonra cizilir)
        window.draw(player); 
        
        window.display();
    }

    return 0;
}