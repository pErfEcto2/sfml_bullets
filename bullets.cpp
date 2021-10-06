#include "bullets.h"
#include "cmath"

Bullet::Bullet(Vector2f pos, Vector2f target): pos(pos), target(target) {
	bullet.setPosition(pos);
	bullet.setSize(bulletSize);
	bullet.setOrigin(Vector2f(bullet.getSize().x / 2, bullet.getSize().y / 2));
	linSpeed = target - pos; // profections of speedX and speedY
	length = sqrt((linSpeed.x * linSpeed.x) + (linSpeed.y * linSpeed.y));
	originalPos = pos;
	linSpeed.x /= length / 5;
	linSpeed.y /= length / 5;
}

void Bullet::update() {
	bullet.move(linSpeed);
}
//
void check() {

}

void Bullet::draw(sf::RenderTarget& rt) {
	rt.draw(bullet);
}