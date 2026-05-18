#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dungeon Crawler - Murat Vuran");
    window.setFramerateLimit(60); 

    sf::RectangleShape player(sf::Vector2f(40.f, 40.f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(380.f, 280.f); 

    float moveSpeed = 5.0f;

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

        // --- SINIR KONTROLLERİ (DUVARLAR) - GÜNCELLENDİ ---
        // Karakterin o anki (X, Y) koordinatini aliyoruz
        sf::Vector2f pos = player.getPosition();

        // X ekseni (Sağ ve Sol) sinirlarini denetle ve pos degiskenini guncelle
        if (pos.x < 0.f) pos.x = 0.f;
        if (pos.x > 760.f) pos.x = 760.f;
        
        // Y ekseni (Alt ve Ust) sinirlarini denetle ve pos degiskenini guncelle
        if (pos.y < 0.f) pos.y = 0.f;
        if (pos.y > 560.f) pos.y = 560.f;

        // Hesaplama bittikten sonra, temiz ve duzeltilmis konumu tek seferde uygula!
        player.setPosition(pos);

        // --- CIZIM ASAMASI ---
        window.clear(sf::Color::Black);
        window.draw(player);
        window.display();
    }

    return 0;
}