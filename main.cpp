#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "unistd.h"
#include "iostream"
#include "bullets.h"
#include "cmath"
#include "vector"
#include "ctime"
#include <sys/time.h>
#include <chrono>

using namespace sf;
using namespace std;
using std::chrono::duration_cast;
using std::chrono::system_clock;

// this fun returns "true" if sprite crosses rect
bool intersects(RectangleShape &rect, Sprite &sprite) {
    FloatRect r1 = rect.getGlobalBounds();
    FloatRect r2 = sprite.getGlobalBounds();
    return r1.intersects(r2);
}

double validate(double angle, Vector2i r, Vector2i m) {
    if (m.x <= r.x && m.y >= r.y) return abs(angle);
    else if (m.x < r.x && m.y <= r.y) return 180 - abs(angle);
    else if (m.x > r.x && m.y <= r.y) return -180 - angle;
    else if (m.x >= r.x && m.y > r.y) return angle;
    else return NULL;
}

double getAngle(RectangleShape &rect) {
    Vector2i r = Vector2i(rect.getPosition());
    Vector2i m = Mouse::getPosition();
    double len = sqrtf64(pow(m.x - r.x, 2) + pow(m.y - r.y, 2));
    double angle = asinf64(abs(m.y - r.y) / len) * 180 / M_PI - 90;
    if (validate(angle, r, m)) return validate(angle, r, m);
}

unsigned long long int getTimeMillisec() {
    return duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch()).count();
}

int main() {
    RenderWindow window(VideoMode(100, 100), "Screen Saver", Style::Fullscreen);
    Event event;

    unsigned long long int timeMillisec = getTimeMillisec();
    int monitorWidth = VideoMode::getDesktopMode().width;
    int monitorHeight = VideoMode::getDesktopMode().height;
    int speedY = 0;
    int speedX = 0;
    int delay = 10000;

    //time_t timeSeconds = time(nullptr);

    vector<Bullet> bulletVec;

    RectangleShape man(Vector2f(2, 20));
    man.setFillColor(Color::Cyan);

    man.setOrigin(Vector2f(man.getLocalBounds().width / 2, man.getLocalBounds().height / 2));
    man.setPosition(Vector2f(monitorWidth / 2, monitorHeight / 2));

    while (window.isOpen()) {
        while (window.pollEvent(event)){
            if (event.type == sf::Event::EventType::Closed) {
                window.close();
                return EXIT_SUCCESS;
            }
        }

        unsigned long long int currentTime = getTimeMillisec();

        if (Keyboard::isKeyPressed(Keyboard::Space) && currentTime > timeMillisec + 500) {
                Bullet bullet(man.getPosition(), Vector2f(Mouse::getPosition()));
                bulletVec.push_back(bullet);
                timeMillisec = getTimeMillisec();
        }
        
        man.setRotation(getAngle(man));

        window.clear();

        for (int i = 0; i < bulletVec.size(); i++) {
            bulletVec[i].update();
            bulletVec[i].draw(window);
        }

        window.draw(man);

        window.display();
        usleep(delay);
    }
}