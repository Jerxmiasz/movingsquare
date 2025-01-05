// Filename: msq.cpp
// Author: 80% Jeremias Villagrán 20% Google Gemini

#include "msq.hpp"

#define PLAYERSPEED .1

msq::msq() : mainWindow(sf::VideoMode({320,320}), "MovingSquare"), player({0,0}, {TILESIZE*2, TILESIZE*2}), inGame(false) {
    
    player.setFillColor(sf::Color::Red);
}

void msq::loadLevel() {

    if (inGame){
        return;
    };

    pugi::xml_document levelDoc;
    pugi::xml_parse_result result = levelDoc.load_file("C:/Users/yudib/OneDrive/Desktop/Jeremias/Proyectos/moving square/levels/level.xml");
    if (!result){
        std::fprintf(stderr, "Error loading level file: %s\n", result.description());
        return;
    };
    pugi::xml_node elementsNode = levelDoc.child("level").child("elements");
    for (pugi::xml_node element : elementsNode.children()){
        std::string eType = element.attribute("type").as_string();
        if (eType == "square"){
            square retrievedSquare(
                {element.attribute("x").as_float(), element.attribute("y").as_float()},
                {element.attribute("width").as_float(), element.attribute("height").as_float()}
            );
            retrievedSquare.setFillColor(parseColor(element.attribute("color").as_string()));
            this->elements.push_back(std::make_unique<square>(retrievedSquare));
        };
        if (eType == "circle"){
            sf::CircleShape retrievedCircle(element.attribute("width").as_float() / 2);
            retrievedCircle.setPosition({element.attribute("x").as_float(), element.attribute("y").as_float()});
            retrievedCircle.setFillColor(parseColor(element.attribute("color").as_string()));
            this->elements.push_back(std::make_unique<sf::CircleShape>(retrievedCircle));
        };
    };
    this->inGame = true;
};

sf::Color msq::parseColor(std::string rgb) {
    short r, g, b;
    sscanf(rgb.c_str(), "%hd, %hd, %hd", &r,&g,&b);
    if (r > 255 || g > 255 || b > 255){
        std::fprintf(stderr, "Invalid color, you want to overflow memory, dont you?:  %s\n", rgb.c_str());
        return sf::Color(255,255,255);
    }
    return sf::Color(r,g,b);
}

void msq::onLoad(){
    this->loadLevel();
    
};

void msq::onUpdate(){
    // Key callback to reset player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::R)){
        this->player.setPosition({1,1});
    }
    // Iterate over all elements for handling collisions
    for (std::unique_ptr<sf::Shape> &element : elements){
        // Get boolean value for bottom collision
        for (std::unique_ptr<sf::Shape> &element : elements){
            if (player.isBottomCollidingWith(element.get()->getGlobalBounds()) && !this->player.jumpDebounce){
                player.isBottomColliding = true;
                break;
            };
            this->player.isBottomColliding = false;
        };
        // Get key callbacks for moving left and right

        // Handle collisions with the window borders
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) && player.getPosition().x > 0){
            player.move({-PLAYERSPEED, 0});
        };
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) && player.getPosition().x < mainWindow.getSize().x - player.getSize().x){
            player.move({PLAYERSPEED, 0});
        };
        // Manage space button callback for jumping
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space) && player.isBottomColliding){
            if (!this->player.jumpDebounce){
                this->player.jumpClock.restart();
                this->player.jumpDebounce = true;
                fprintf(stdout, "space");
            };
        };
        // If jumping but jumping time is over
        if (this->player.jumpDebounce == true && this->player.jumpClock.getElapsedTime().asMilliseconds() >= 200 && !this->player.isBottomColliding){
            // Fall
            this->player.jumpDebounce = false;
            this->player.jumpClock.reset();
        }

        // if is falling
        if (!this->player.isBottomColliding && !this->player.jumpDebounce){
            this->player.verticalSpeed = 1;
        // if is not falling (touching ground)
        }else if (this->player.isBottomColliding && !this->player.jumpDebounce){
            this->player.verticalSpeed = 0;
        // Handle jump speed
        }else if (this->player.jumpDebounce && !this->player.isBottomColliding){
            int32_t timeElapsed = this->player.jumpClock.getElapsedTime().asMilliseconds();
            if (timeElapsed >= 50 && timeElapsed <= 100){
                this->player.verticalSpeed = -0.40;
            };
            if (timeElapsed >= 100 && timeElapsed <= 140){
                this->player.verticalSpeed = -.80;
            };
            if (timeElapsed >= 130 && timeElapsed <= 160){
                this->player.verticalSpeed = -1;
            };
            if (timeElapsed >= 160 && timeElapsed <= 200){
                this->player.verticalSpeed = -.80;
            }
        }
    };
    this->player.move({0, this->player.verticalSpeed});
    
}

void msq::onRender(){
    mainWindow.clear(sf::Color(100,100,100));
    mainWindow.draw(this->player);
    if (this->inGame){
        for (std::unique_ptr<sf::Shape> &element : elements){
            mainWindow.draw(*element);
        };
    };
    mainWindow.display();
};

