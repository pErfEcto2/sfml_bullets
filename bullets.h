#pragma once
#include "iostream"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
using namespace std;
using namespace sf;

class Bullet {
    public:
	    Bullet(Vector2f pos, Vector2f target);
	    void update();
		void check();
		void draw(RenderTarget& rt);
    private:
    	RectangleShape bullet;
		Vector2f pos;
		Vector2f target;
		Vector2f bulletSize = Vector2f(3, 3);
		Vector2f linSpeed;
		double length;
		Vector2f originalPos;
};