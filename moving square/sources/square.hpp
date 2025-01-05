#pragma once

#include <SFML/Graphics.hpp>
#include <thread>

// Wrapper of sf::rectangleShape that adds boundaries
class square : public sf::RectangleShape {
    public:
        square(sf::Vector2f pos, sf::Vector2f size){
            this->setPosition(pos);
            this->setSize(size);
        };
        sf::FloatRect BottomBounds() {
            sf::FloatRect gbBounds = this->getGlobalBounds();
            return sf::FloatRect({gbBounds.position.x, gbBounds.position.y + gbBounds.size.y}, {gbBounds.size.x, 1});
        };
        sf::FloatRect RightBounds() {
            sf::FloatRect gbBounds = this->getGlobalBounds();
            return sf::FloatRect({gbBounds.position.x + gbBounds.size.x, gbBounds.position.y}, {gbBounds.size.x, gbBounds.size.y});
        };
        sf::FloatRect LeftBounds() {
            sf::FloatRect gbBounds = this->getGlobalBounds();
            return sf::FloatRect({gbBounds.position.x, gbBounds.position.y}, {1, gbBounds.size.y});
        };
        
        float horizontalSpeed = .2;
        float verticalSpeed = 0;
        bool isBottomColliding = false;
        sf::Clock jumpClock;
        bool jumpDebounce = false;
    
        bool isBottomCollidingWith(sf::FloatRect bounds)
        {
            if (this->BottomBounds().findIntersection(bounds).has_value()){
                return true;
            }else{
                return false;
            }
        };
        
};
