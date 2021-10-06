#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "unistd.h"
#include "iostream"
#include "random"
using namespace sf;
using namespace std;
// this fun returns "true" if sprite crosses rect
bool intersects(RectangleShape &rect, Sprite &sprite) {
    FloatRect r1 = rect.getGlobalBounds();
    FloatRect r2 = sprite.getGlobalBounds();
    return r1.intersects(r2);
}
int main() {
    RenderWindow window(VideoMode(100, 100), "Screen Saver", Style::Fullscreen);
    Event event;
    int monitorWidth = VideoMode::getDesktopMode().width;
    int monitorHeight = VideoMode::getDesktopMode().height;
    int speedY = 0;
    int speedX = 0;
    int delay = 1000;
    Texture texture; // ball's texture
    Sprite ball;
    srand(static_cast<unsigned int>(time(0)));
    if (!texture.loadFromFile("/home/projects/cpp/screen_saver/src/ball.png")) {
        cout << "Failed while loading photo" << endl;
        return EXIT_FAILURE;
    }
    ball.setTexture(texture);
    ball.setScale(Vector2f(0.2, 0.2));
    ball.setPosition(Vector2f(monitorWidth / 2 - 52, monitorHeight / 2 - 52));
    // set initial speed
    speedX = 1 + rand() % 2;
    speedY = 1 + rand() % 2;
    RectangleShape floor(Vector2f(monitorWidth, 30));
    floor.setPosition(Vector2f(0, monitorHeight));
    RectangleShape rightWall(Vector2f(30, monitorHeight));
    rightWall.setPosition(Vector2f(monitorWidth, 0));
    RectangleShape leftWall(Vector2f(30, monitorHeight));
    RectangleShape topWall(Vector2f(monitorWidth, 30));
    Font font;
    Text text;
    if (!font.loadFromFile("/home/projects/cpp/screen_saver/src/font.ttf")) {
        cout << "Failed while loading font" << endl;
        return EXIT_FAILURE;
    }
    text.setFont(font);
    text.setString("PRESS ESCAPE TO EXIT");
    text.setCharacterSize(30);
    while (window.isOpen()) {
        while (window.pollEvent(event)){
            if (event.type == sf::Event::EventType::Closed) {
                window.close();
                return EXIT_SUCCESS;
            }
        }
        
        

        window.clear();
        window.draw(text);
        window.draw(ball);
        window.display();
        usleep(delay);
    }
}