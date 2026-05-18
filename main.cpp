#include <SFML/Graphics.hpp>

int main() {
    // 800x600 boyutlarinda pencere
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dungeon Crawler - Murat Vuran");
    window.setFramerateLimit(60); 

    // Karakterimizi olusturalim (40x40 boyutunda)
    sf::RectangleShape player(sf::Vector2f(40.f, 40.f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(380.f, 280.f); 

    float moveSpeed = 5.0f;

    // Oyun dongusu
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // --- HAREKET KONTROLLERİ ---
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.move(0.f, -moveSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.move(0.f, moveSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.move(-moveSpeed, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.move(moveSpeed, 0.f);
        }

        // --- SINIR KONTROLLERİ (DUVARLAR) ---
        // Karakterin o anki (X, Y) koordinatini aliyoruz
        sf::Vector2f pos = player.getPosition();

        // Sol duvar carpismasi (X sifirdan kucuk olamaz)
        if (pos.x < 0.f) player.setPosition(0.f, pos.y);
        
        // Sag duvar carpismasi (Pencere 800 genisliginde, karakter 40 genisliginde. 800-40 = 760)
        if (pos.x > 760.f) player.setPosition(760.f, pos.y);
        
        // Ust duvar carpismasi (Y sifirdan kucuk olamaz)
        if (pos.y < 0.f) player.setPosition(pos.x, 0.f);
        
        // Alt duvar carpismasi (Pencere 600 yuksekliginde, karakter 40. 600-40 = 560)
        if (pos.y > 560.f) player.setPosition(pos.x, 560.f);

        // --- CIZIM ASAMASI ---
        window.clear(sf::Color::Black);
        window.draw(player);
        window.display();
    }

    return 0;
}