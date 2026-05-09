#include <SFML/Graphics.hpp>

int main() {
    // 800x600 boyutlarinda bir pencere olusturuyoruz
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dungeon Crawler - Murat Vuran (SFML OK)");

    // Oyun dongusu: Pencere acik oldugu surece calisir
    while (window.isOpen()) {
        sf::Event event;
        // Kullanici carpiya basarsa pencereyi kapatma mantigi
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Ekrani tamamen siyaha boya (temizle)
        window.clear(sf::Color::Black);

        // Ileride karakterlerimizi buraya cizecegiz

        // Ekrani goster
        window.display();
    }

    return 0;
}