#include "msq.hpp"

int main(){
    msq game;
    game.onLoad();
    while (game.mainWindow.isOpen()){
        while (const std::optional<sf::Event> &event = game.mainWindow.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                game.mainWindow.close();
            };
        }
        
        game.onUpdate();
        game.onRender();
    };
    return 0;
}