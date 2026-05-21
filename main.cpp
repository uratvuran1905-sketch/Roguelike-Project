#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Pencereyi olustur ve fps'i sabitle (yoksa karakter ucuyor)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dungeon Crawler - Murat Vuran");
    window.setFramerateLimit(60); 

    // Zemin texture ve sprite ayarlari
    sf::Texture floorTexture;
    if (!floorTexture.loadFromFile("../../assets/floor.png")) {
        std::cout << "HATA: floor resmi yok!" << std::endl;
    }
    sf::Sprite floorSprite;
    floorSprite.setTexture(floorTexture);

    // Bizim karakterin ayarlari
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../../assets/player.png")) {
        std::cout << "HATA: player resmi yok!" << std::endl;
    }
    sf::Sprite player;
    player.setTexture(playerTexture);
    player.setScale(0.5f, 0.5f); // resmi yariya kuculttuk
    player.setPosition(380.f, 280.f); 

    // Dusman ayarlari
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("../../assets/enemy.png")) {
        std::cout << "HATA: enemy resmi yok!" << std::endl;
    }
    sf::Sprite enemy;
    enemy.setTexture(enemyTexture);
    enemy.setScale(0.20f, 0.20f); 
    enemy.setPosition(700.f, 500.f); // sag alt kosede dogsun

    // Hizlar (dusman bizden yavas olmali)
    float playerSpeed = 5.0f;
    float enemySpeed = 2.0f; 

    // Oyun dongusu basliyor
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // WASD klavye okuma
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.move(0.f, -playerSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.move(0.f, playerSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.move(-playerSpeed, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.move(playerSpeed, 0.f);

        // Ekrandan disari cikma bug'ini onlemek icin sinir kontrolu
        sf::Vector2f playerPos = player.getPosition();
        float playerW = player.getGlobalBounds().width;
        float playerH = player.getGlobalBounds().height;

        if (playerPos.x < 0.f) playerPos.x = 0.f;
        if (playerPos.x > 800.f - playerW) playerPos.x = 800.f - playerW;
        if (playerPos.y < 0.f) playerPos.y = 0.f;
        if (playerPos.y > 600.f - playerH) playerPos.y = 600.f - playerH;
        player.setPosition(playerPos);

        // Basit yapay zeka: Dusmanin X ve Y'sini oyuncuya gore guncelle (takip et)
        sf::Vector2f enemyPos = enemy.getPosition();
        
        if (enemyPos.x < playerPos.x) enemy.move(enemySpeed, 0.f);
        if (enemyPos.x > playerPos.x) enemy.move(-enemySpeed, 0.f);
        
        if (enemyPos.y < playerPos.y) enemy.move(0.f, enemySpeed);
        if (enemyPos.y > playerPos.y) enemy.move(0.f, -enemySpeed);

        // Cizim kismi - Once zemin, sonra dusman, en son biz
        window.clear(sf::Color::Black);
        
        float tileW = floorSprite.getGlobalBounds().width;
        float tileH = floorSprite.getGlobalBounds().height;
        if (tileW > 0 && tileH > 0) {
            for (float x = 0; x < 800; x += tileW) {
                for (float y = 0; y < 600; y += tileH) {
                    floorSprite.setPosition(x, y);
                    window.draw(floorSprite); 
                }
            }
        }

        window.draw(enemy);  
        window.draw(player); 
        
        window.display();
    }

    return 0;
}