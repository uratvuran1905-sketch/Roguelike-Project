#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include <string>  

int main() {
    srand(static_cast<unsigned>(time(NULL)));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Dungeon Crawler - Murat Vuran");
    window.setFramerateLimit(60); 

    // --- GORSELLER ---
    sf::Texture floorTexture;
    if (!floorTexture.loadFromFile("../../assets/floor.png")) std::cout << "HATA: floor!" << std::endl;
    sf::Sprite floorSprite(floorTexture);

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../../assets/player.png")) std::cout << "HATA: player!" << std::endl;
    sf::Sprite player(playerTexture);
    player.setScale(0.5f, 0.5f); 
    player.setPosition(380.f, 280.f); 

    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("../../assets/enemy.png")) std::cout << "HATA: enemy!" << std::endl;
    sf::Sprite enemy(enemyTexture);
    enemy.setScale(0.20f, 0.20f); 
    enemy.setPosition(700.f, 500.f); 

    sf::Texture coinTexture;
    if (!coinTexture.loadFromFile("../../assets/coin.png")) std::cout << "HATA: coin!" << std::endl;
    sf::Sprite coin(coinTexture);
    coin.setScale(0.25f, 0.25f); 
    coin.setPosition(200.f, 200.f); 

    sf::Texture potionTexture;
    if (!potionTexture.loadFromFile("../../assets/potion.png")) std::cout << "HATA: potion!" << std::endl;
    sf::Sprite potion(potionTexture);
    potion.setScale(0.15f, 0.15f); 

    // --- ZAMANLAYICI VE OYUN DURUMU DEGISKENLERI ---
    sf::Clock potionClock; 
    bool isPotionActive = false; 
    float nextSpawnTime = 10.0f + (rand() % 6); 

    // OYUN DURUMU: 0 = Menu, 1 = Oynanis, 2 = Game Over
    int gameState = 0; 
    
    float playerHP = 200.f; 
    float playerSpeed = 5.0f;
    float enemySpeed = 2.0f; // Menude degisecek

    sf::Font font;
    if (!font.loadFromFile("../../assets/arial.ttf")) std::cout << "HATA: font yok!" << std::endl;

    int score = 0;
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(20.f, 50.f); 

    // YENI: MENU YAZISI
    sf::Text menuText;
    menuText.setFont(font);
    menuText.setString("DUNGEON CRAWLER\n\nZorluk Seviyesi Seciniz:\n\n[1] Kolay (Yavas Dusman)\n[2] Orta  (Hizli Dusman)\n[3] Zor   (Kacis Yok!)");
    menuText.setCharacterSize(35);
    menuText.setFillColor(sf::Color::White);
    menuText.setPosition(150.f, 150.f);

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER\nMenuye Donmek Icin 'R'ye Bas");
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(120.f, 250.f); 

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        // --- DURUM 0: ANA MENU ---
        if (gameState == 0) {
            // Klavyeden zorluk secimi
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
                enemySpeed = 1.3f; 
                gameState = 1; // Oyunu baslat
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
                enemySpeed = 2.4f; 
                gameState = 1; 
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) {
                enemySpeed = 3.0f; // Oyuncudan hizli!
                gameState = 1; 
            }
        }
        // --- DURUM 1: OYNANIS ---
        else if (gameState == 1) {
            // Hareket
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.move(0.f, -playerSpeed);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.move(0.f, playerSpeed);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.move(-playerSpeed, 0.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.move(playerSpeed, 0.f);

            // Sinirlar
            sf::Vector2f playerPos = player.getPosition();
            if (playerPos.x < 0.f) playerPos.x = 0.f;
            if (playerPos.x > 800.f - player.getGlobalBounds().width) playerPos.x = 800.f - player.getGlobalBounds().width;
            if (playerPos.y < 0.f) playerPos.y = 0.f;
            if (playerPos.y > 600.f - player.getGlobalBounds().height) playerPos.y = 600.f - player.getGlobalBounds().height;
            player.setPosition(playerPos);

            // Dusman
            sf::Vector2f enemyPos = enemy.getPosition();
            if (enemyPos.x < playerPos.x) enemy.move(enemySpeed, 0.f);
            if (enemyPos.x > playerPos.x) enemy.move(-enemySpeed, 0.f);
            if (enemyPos.y < playerPos.y) enemy.move(0.f, enemySpeed);
            if (enemyPos.y > playerPos.y) enemy.move(0.f, -enemySpeed);

            // Hasar Alma
            if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
                playerHP -= 1.0f; 
                if (playerHP <= 0.f) {
                    playerHP = 0.f;
                    gameState = 2; // Can bitti, Durum 2'ye (Game Over) gec
                }
            }

            // Altin Toplama
            if (player.getGlobalBounds().intersects(coin.getGlobalBounds())) {
                score += 10; 
                coin.setPosition(rand() % 750, rand() % 550);
            }

            // IKSIR MANTIGI
            float gecenZaman = potionClock.getElapsedTime().asSeconds(); 

            if (!isPotionActive) {
                if (gecenZaman >= nextSpawnTime) {
                    isPotionActive = true; 
                    potion.setPosition(rand() % 750, rand() % 550);
                    potionClock.restart(); 
                }
            } else {
                if (gecenZaman >= 3.0f) {
                    isPotionActive = false; 
                    nextSpawnTime = 10.0f + (rand() % 6); 
                    potionClock.restart(); 
                }
                else if (player.getGlobalBounds().intersects(potion.getGlobalBounds())) {
                    playerHP += 40.f; 
                    if (playerHP > 200.f) playerHP = 200.f; 
                    
                    isPotionActive = false; 
                    nextSpawnTime = 10.0f + (rand() % 6); 
                    potionClock.restart(); 
                }
            }
            
            scoreText.setString("Skor: " + std::to_string(score));
        } 
        // --- DURUM 2: GAME OVER ---
        else if (gameState == 2) {
            // Restart atildiginda direkt menuye (Durum 0) atiyoruz
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                gameState = 0; // Menuye don
                playerHP = 200.f;
                score = 0;
                player.setPosition(380.f, 280.f);
                enemy.setPosition(700.f, 500.f);
                
                isPotionActive = false;
                nextSpawnTime = 10.0f + (rand() % 6);
                potionClock.restart();
            }
        }

        // --- CIZIM ASAMASI ---
        window.clear(sf::Color::Black);
        
        // Eger menudeysek sadece menu yazisini ciz
        if (gameState == 0) {
            window.draw(menuText);
        }
        // Oyundaysak veya olmussek (Game Over ekrani) zindani ciz
        else if (gameState == 1 || gameState == 2) {
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

            window.draw(coin);
            if (isPotionActive) window.draw(potion); 
            window.draw(enemy);  
            window.draw(player); 
            
            for (int i = 0; i < 10; i++) {
                if (playerHP > i * 20.f) {
                    sf::RectangleShape hpBlock(sf::Vector2f(15.f, 20.f)); 
                    hpBlock.setFillColor(sf::Color::Green);
                    hpBlock.setPosition(20.f + (i * 20.f), 20.f); 
                    window.draw(hpBlock);
                }
            }

            window.draw(scoreText);

            if (gameState == 2) window.draw(gameOverText);
        }
        
        window.display();
    }

    return 0;
}