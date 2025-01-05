#include "SFML/Graphics.hpp"
#include "square.hpp"
#include "pugi.hpp"
#include <memory>
#include <chrono>

#define TILESIZE 16

class msq {
    public:
        msq();
        
        void onLoad();
        void onUpdate();
        void onRender();
        sf::RenderWindow mainWindow;
    private:
        square player;
        bool inGame;
        std::vector<std::unique_ptr<sf::Shape>> elements;
        
        sf::Color parseColor(std::string rgb);
        void loadLevel();
};
