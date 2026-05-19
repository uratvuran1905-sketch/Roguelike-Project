#include <SFML/Graphics.hpp>
#include <iostream> // Hata mesajlarini konsola yazdirmak icin eklendi

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dungeon Crawler - Murat Vuran");
    window.setFramerateLimit(60); 

    // --- GORSELLIK (TEXTURE & SPRITE) ASAMASI ---
    // 1. Dokuyu (Resmi) olustur ve assets klasorunden yukle
    sf::Texture playerTexture;
   if (!playerTexture.loadFromFile("../../assets/player.png")) {
        // Eger resmi bulamazsa veya isim yanlissa bize haber verecek
        std::cout << "HATA: player.png dosyasi assets klasorunde bulunamadi!" << std::endl;
    }

   // 2. Sprite (Oyun Ici Obje) olustur ve az onceki dokuyu ona giydir
    sf::Sprite player;
    player.setTexture(playerTexture);

    // Karakterin boyutunu yatayda ve dikeyde yari yariya kucult
    player.setScale(0.4f, 0.4f);
    
    // Karakterin baslangic konumu
    player.setPosition(380.f, 280.f); 

    float moveSpeed = 5.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // --- HAREKET KONTROLLERİ ---
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.move(0.f, -moveSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.move(0.f, moveSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.move(-moveSpeed, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.move(moveSpeed, 0.f);

        // --- SINIR KONTROLLERİ ---
        sf::Vector2f pos = player.getPosition();
        
        // Yeni resmin genisligini ve yuksekligini oyuna otomatik hesaplatiyoruz ki sinirlar sasmasin
        float playerWidth = player.getGlobalBounds().width;
        float playerHeight = player.getGlobalBounds().height;

        if (pos.x < 0.f) pos.x = 0.f;
        if (pos.x > 800.f - playerWidth) pos.x = 800.f - playerWidth;
        if (pos.y < 0.f) pos.y = 0.f;
        if (pos.y > 600.f - playerHeight) pos.y = 600.f - playerHeight;

        player.setPosition(pos);

        // --- CIZIM ASAMASI ---
        window.clear(sf::Color::Black);
        
        window.draw(player); // Artik yesil kutuyu degil, gercek resmimizi ciziyoruz
        
        window.display();
    }

    return 0;
}