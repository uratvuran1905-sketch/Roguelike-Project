#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib> // rand() icin (rastgele konum)
#include <ctime>   // rastgeleligi zamana baglamak icin
#include <string>  // yazilari birlestirmek icin

int main() {
    // Rastgelelik tohumu (oyun her acildiginda altin farkli yerde dogsun diye)
    srand(static_cast<unsigned>(time(NULL)));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Dungeon Crawler - Murat Vuran");
    window.setFramerateLimit(60); 

    // --- GORSELLERI YUKLEME ---
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

    // --- YENI: TOPLANABILIR ALTIN ---
    sf::Texture coinTexture;
    if (!coinTexture.loadFromFile("../../assets/coin.png")) std::cout << "HATA: coin!" << std::endl;
    sf::Sprite coin(coinTexture);
    coin.setScale(0.3f, 0.3f); 
    coin.setPosition(200.f, 200.f); // Ilk dogdugu yer

    // --- ARAYUZ VE CAN SİSTEMİ ---
    float playerHP = 200.f; 
    sf::RectangleShape hpBar(sf::Vector2f(playerHP, 20.f));
    hpBar.setFillColor(sf::Color::Green);
    hpBar.setPosition(20.f, 20.f);

    // --- YENI: YAZI (TEXT) AYARLARI ---
    sf::Font font;
    if (!font.loadFromFile("../../assets/arial.ttf")) std::cout << "HATA: font yok!" << std::endl;

    int score = 0;
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(20.f, 50.f); // Can barinin altina koyduk

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(180.f, 250.f); // Ekranin ortasi

    // Hizlar ve Oyun Durumu
    float playerSpeed = 5.0f;
    float enemySpeed = 2.0f; 
    bool isGameOver = false; // Baslangicta yasiyoruz

    // --- OYUN DONGUSU ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        // Eger can bitmediyse (oyun devam ediyorsa) hareket et
        if (!isGameOver) {
            // WASD
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.move(0.f, -playerSpeed);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.move(0.f, playerSpeed);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.move(-playerSpeed, 0.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.move(playerSpeed, 0.f);

            // Sinir kontrolu
            sf::Vector2f playerPos = player.getPosition();
            if (playerPos.x < 0.f) playerPos.x = 0.f;
            if (playerPos.x > 800.f - player.getGlobalBounds().width) playerPos.x = 800.f - player.getGlobalBounds().width;
            if (playerPos.y < 0.f) playerPos.y = 0.f;
            if (playerPos.y > 600.f - player.getGlobalBounds().height) playerPos.y = 600.f - player.getGlobalBounds().height;
            player.setPosition(playerPos);

            // Dusman takibi
            sf::Vector2f enemyPos = enemy.getPosition();
            if (enemyPos.x < playerPos.x) enemy.move(enemySpeed, 0.f);
            if (enemyPos.x > playerPos.x) enemy.move(-enemySpeed, 0.f);
            if (enemyPos.y < playerPos.y) enemy.move(0.f, enemySpeed);
            if (enemyPos.y > playerPos.y) enemy.move(0.f, -enemySpeed);

            // Hasar alma kontrolu
            if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
                playerHP -= 1.0f; 
                if (playerHP <= 0.f) {
                    playerHP = 0.f;
                    isGameOver = true; // Can sifirlandi, oyunu durdur
                }
                hpBar.setSize(sf::Vector2f(playerHP, 20.f)); 
            }

            // --- YENI: ALTIN TOPLAMA KONTROLU ---
            if (player.getGlobalBounds().intersects(coin.getGlobalBounds())) {
                score += 10; // Skoru artir
                // Altini ekranda baska bir rastgele noktaya isinla (ekran disina cikmasin diye sinir cizdik)
                float rastgeleX = rand() % 750;
                float rastgeleY = rand() % 550;
                coin.setPosition(rastgeleX, rastgeleY);
            }
        }

        // Skor yazisini guncelle
        scoreText.setString("Skor: " + std::to_string(score));

        // --- CIZIM ASAMASI ---
        window.clear(sf::Color::Black);
        
        // Zemin ciz
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

        // Oyunda her seyi ciz
        window.draw(coin);
        window.draw(enemy);  
        window.draw(player); 
        window.draw(hpBar);
        window.draw(scoreText);

        // Eger olduysak ekrana kocaman GAME OVER bas
        if (isGameOver) {
            window.draw(gameOverText);
        }
        
        window.display();
    }

    return 0;
}