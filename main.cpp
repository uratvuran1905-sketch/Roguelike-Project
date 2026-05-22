#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Pencere ayari
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dungeon Crawler - Murat Vuran");
    window.setFramerateLimit(60); 

    // Zemin
    sf::Texture floorTexture;
    if (!floorTexture.loadFromFile("../../assets/floor.png")) std::cout << "HATA: floor!" << std::endl;
    sf::Sprite floorSprite;
    floorSprite.setTexture(floorTexture);

    // Bizim karakter
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../../assets/player.png")) std::cout << "HATA: player!" << std::endl;
    sf::Sprite player;
    player.setTexture(playerTexture);
    player.setScale(0.5f, 0.5f); 
    player.setPosition(380.f, 280.f); 

    // Dusman (Gecen sefer ayarladigimiz 0.20 oraninda)
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("../../assets/enemy.png")) std::cout << "HATA: enemy!" << std::endl;
    sf::Sprite enemy;
    enemy.setTexture(enemyTexture);
    enemy.setScale(0.20f, 0.20f); 
    enemy.setPosition(700.f, 500.f); 

    // --- YENI: CAN SİSTEMİ ---
    float playerHP = 200.f; // Toplam canimiz
    
    // Ekrana cizilecek yesil can bari (Genislik: 200, Yukseklik: 20)
    sf::RectangleShape hpBar(sf::Vector2f(playerHP, 20.f));
    hpBar.setFillColor(sf::Color::Green);
    hpBar.setPosition(20.f, 20.f); // Sol ust kosede dursun

    float playerSpeed = 5.0f;
    float enemySpeed = 2.0f; 

    // Oyun dongusu
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // --- HAREKET KONTROLLERİ ---
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.move(0.f, -playerSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.move(0.f, playerSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.move(-playerSpeed, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.move(playerSpeed, 0.f);

        // --- EKRANDAN CIKMA KONTROLU ---
        sf::Vector2f playerPos = player.getPosition();
        float playerW = player.getGlobalBounds().width;
        float playerH = player.getGlobalBounds().height;

        if (playerPos.x < 0.f) playerPos.x = 0.f;
        if (playerPos.x > 800.f - playerW) playerPos.x = 800.f - playerW;
        if (playerPos.y < 0.f) playerPos.y = 0.f;
        if (playerPos.y > 600.f - playerH) playerPos.y = 600.f - playerH;
        player.setPosition(playerPos);

        // --- YAPAY ZEKA TAKİP ---
        sf::Vector2f enemyPos = enemy.getPosition();
        
        if (enemyPos.x < playerPos.x) enemy.move(enemySpeed, 0.f);
        if (enemyPos.x > playerPos.x) enemy.move(-enemySpeed, 0.f);
        if (enemyPos.y < playerPos.y) enemy.move(0.f, enemySpeed);
        if (enemyPos.y > playerPos.y) enemy.move(0.f, -enemySpeed);

        // --- YENI: CARPISMA (HASAR ALMA) KONTROLU ---
        // Eger dusmanin sinirlari bizim sinirlarimizla kesisiyorsa (degiyorsa)
        if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            playerHP -= 1.0f; // Cani azalt
            
            // Can sifirin altina inmesin diye sinir koyduk
            if (playerHP < 0.f) playerHP = 0.f; 
            
            // Yesil barin genisligini guncel canimiza gore ayarla
            hpBar.setSize(sf::Vector2f(playerHP, 20.f)); 
        }

        // --- CIZIM ASAMASI ---
        window.clear(sf::Color::Black);
        
        // Zemin cizimi
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
        
        // En son can barini ciziyoruz ki her seyin ustunde gorunsun
        window.draw(hpBar);
        
        window.display();
    }

    return 0;
}