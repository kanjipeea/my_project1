#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class CustomSprite : public sf::Sprite
{
public:
    void setBounds(int left, int right, int top, int bottom) {
        bound_top = top;
        bound_bottom = bottom;
        bound_right = right;
        bound_left = left;
    }

    bool Collision_T(sf::FloatRect wall_bounds, sf::FloatRect guy_bounds)
    {
        if ((guy_bounds.top+guy_bounds.height >= wall_bounds.top-3) && (guy_bounds.top < wall_bounds.top)
            && (guy_bounds.left+guy_bounds.width > wall_bounds.left+3) && (guy_bounds.left < wall_bounds.left+wall_bounds.width-3))
        {
            return 1;
        }
        else{return 0;}

    }
    bool Collision_B(sf::FloatRect wall_bounds, sf::FloatRect guy) {
        return (guy.top <= wall_bounds.top + wall_bounds.height + 3 && guy.top > wall_bounds.top &&
                guy.left + guy.width > wall_bounds.left + 3 && guy.left < wall_bounds.left + wall_bounds.width - 3);
    }

    bool Collision_L(sf::FloatRect wall_bounds, sf::FloatRect guy) {
        return (guy.left + guy.width >= wall_bounds.left - 3 && guy.left < wall_bounds.left &&
                guy.top + guy.height > wall_bounds.top + 3 && guy.top < wall_bounds.top + wall_bounds.height - 3);
    }

    bool Collision_R(sf::FloatRect wall_bounds, sf::FloatRect guy) {
        return (guy.left <= wall_bounds.left + wall_bounds.width + 3 && guy.left > wall_bounds.left &&
                guy.top + guy.height > wall_bounds.top + 3 && guy.top < wall_bounds.top + wall_bounds.height - 3);
    }

    void moveInDirection(const sf::Time &elapsed, const std::vector<sf::Sprite> &obstacles) {
        float dx = 0, dy = 0;
        float speed = 175.0f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) dy -= speed * elapsed.asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) dy += speed * elapsed.asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) dx -= speed * elapsed.asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) dx += speed * elapsed.asSeconds();

        sf::FloatRect nextPos = getGlobalBounds();
        nextPos.left += dx;
        nextPos.top += dy;

        for (const auto& wall : obstacles) {
            sf::FloatRect wallBounds = wall.getGlobalBounds();
            if (nextPos.intersects(wallBounds)) return; // block movement on collision
        }

        if (nextPos.left < bound_left || nextPos.top < bound_top ||
            nextPos.left + nextPos.width > bound_right ||
            nextPos.top + nextPos.height > bound_bottom)
            return;

        move(dx, dy);
    }

private:
    int bound_top = 0;
    int bound_bottom = 0;
    int bound_left = 0;
    int bound_right = 0;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Labyrinth");
    sf::Clock clock;

    sf::Texture guy_tex, grass_tex, wall_tex;
    if (!grass_tex.loadFromFile("grass.png") || !guy_tex.loadFromFile("guy.png") || !wall_tex.loadFromFile("wall.png")){
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    };

    CustomSprite guy;
    guy.setTexture(guy_tex);
    guy.setPosition(100, 300);

    sf::Sprite grass(grass_tex);
    grass.setScale(
        window.getSize().x / (float)grass_tex.getSize().x,
        window.getSize().y / (float)grass_tex.getSize().y);


    std::vector<sf::Sprite> walls;
    sf::Sprite wall1; sf::Sprite wall2; sf::Sprite wall3;
    sf::Sprite wall4; sf::Sprite wall5; sf::Sprite wall6;

    wall1.setTexture(wall_tex);
    wall1.setPosition(200, 100); wall1.setScale(0.5, 2);

    wall2.setTexture(wall_tex);
    wall2.setPosition(400, 0); wall2.setScale(0.6, 1.3);

    wall3.setTexture(wall_tex);
    wall3.setPosition(60, 100); wall3.setScale(0.7, 0.6);

    wall4.setTexture(wall_tex);
    wall4.setPosition(300, 400); wall4.setScale(2, 0.5);

    wall5.setTexture(wall_tex);
    wall5.setPosition(600, 200); wall5.setScale(1, 0.5);

    wall6.setTexture(wall_tex);
    wall6.setPosition(400, 296); wall6.setScale(0.75, 0.17);

    walls.push_back(wall1);
    walls.push_back(wall2);
    walls.push_back(wall3);
    walls.push_back(wall4);
    walls.push_back(wall5);
    walls.push_back(wall6);

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        guy.setBounds(0, window.getSize().x, 0, window.getSize().y);
        guy.moveInDirection(elapsed, walls);

        window.clear(sf::Color::Black);
        window.draw(grass);
        window.draw(guy);

        for (auto &wall : walls){
            window.draw(wall);
        }

        window.display();
    }

    return 0;
}
