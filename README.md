# Roguelike-Project
Kocaeli Üniversitesi YZM104 Programlama II Dersi Oyun Projesi. C++ ve SFML kullanılarak geliştirilen prosedürel zindan (dungeon crawler) oyunu.

# Dungeon Crawler - YZM104 Programlama II Projesi

Geliştirici: Murat Vuran

Proje Amacı: C++ ve SFML kütüphanesi kullanılarak geliştirilmiş, 2D yukarıdan bakış açılı bir hayatta kalma ve zindan keşif oyunudur.

Oyun Mekanikleri:

Hareket: W, A, S, D tuşlarıyla karakter kontrolü.

Zorluk Seviyeleri (Game State): Ana menü üzerinden 3 farklı zorluk seviyesi (Kolay, Orta, Zor) seçimi. Bu seçim düşmanın takip hızını dinamik olarak etkilemektedir.

Yapay Zeka: Düşman karakteri, oyuncunun X ve Y koordinatlarını anlık olarak takip eden temel bir izleme algoritmasına sahiptir.

Çarpışma (Collision): Karakterlerin "Global Bounds" değerleri üzerinden kesişim kontrolü yapılarak hasar alma mantığı kurulmuştur.

Dinamik UI: Oyuncunun can değerine göre azalan veya artan 10 bölmeli (segmented) can barı.

Zamanlayıcı (Timer): sf::Clock kullanılarak belirli saniye aralıklarında rastgele konumlarda beliren ve süresi dolunca kaybolan Can İksiri mekaniği.

Oyun Döngüsü: Can sıfırlandığında "Game Over" durumuna geçiş ve 'R' tuşu ile tüm değişkenlerin sıfırlanarak oyunun yeniden başlatılması.

Derleme: Proje klasöründeki CMakeLists.txt dosyası kullanılarak derlenebilir.
