cmake_minimum_required(VERSION 3.14)
project(RoguelikeGame)

# Bu kisim SFML kutuphanesini otomatik olarak indirir ve projeye baglar
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

add_executable(RoguelikeGame main.cpp)

# Kodumuzun SFML'nin grafik, pencere ve sistem ozelliklerini kullanacagini belirtiyoruz
target_link_libraries(RoguelikeGame PRIVATE sfml-graphics sfml-window sfml-system)