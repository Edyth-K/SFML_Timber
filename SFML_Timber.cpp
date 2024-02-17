#include <SFML/Graphics.hpp>
#include <iostream>
// make code easier to type?
using namespace sf;

// This is where the game starts from
int main() {
	// create a video mode object
	VideoMode vm(1280, 720);

	// create and open window for game
	RenderWindow window(vm, "Timber", Style::Default);

	// Create a texture to hold a graphic on the GPU and load image to it
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/background.png");
	// create sprite and attach texture to it
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	// Create tree
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition((1280 / 2)-75, -320);

	// Create bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 300);
	spriteBee.scale(0.15, 0.15);
	// speed
	float beeSpeed = 0.1f;
	// is active?
	bool beeActive = false;
	// direction: true -> | false <-
	bool beeFace = false;

	// Create Clouds
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	Sprite spriteCloud[3];
	bool cloudActive[3];
	float cloudSpeed[3];
	for (int i = 0; i < 3; i++)
	{
		spriteCloud[i].setTexture(textureCloud);
		spriteCloud[i].scale(.5, .5);
		spriteCloud[i].setPosition(0, i * 100);
		cloudActive[i] = false;
		cloudSpeed[i] = 0.0f;
	}


	// control time
	Clock clock;

	// Basic Game Loop
	while (window.isOpen())
	{
		/*
		* Handle Player Input
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		* Update Scene
		*/
		 
		// measure time
		Time dt = clock.restart();


		// setup bee
		if (!beeActive) {
			// bee speed
			srand((int)time(0));
			beeSpeed = (rand() % 200) + 200; // random number between 200 and 399

			// bee height
			srand((int)time(0) * 10);
			float height = (rand() % 500); // random number between 500 and 999
			spriteBee.setPosition(1300, height);
			beeActive = true;
		}
		else
		// move the bee
		{
			spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);
			if (spriteBee.getPosition().x < -100)
			{
				beeActive = false;
			}
		}

		// manage clouds
		for (int i = 0; i < 3; i++)
		{
			if (!cloudActive[i])
			{
				srand((int)time(0) * i*10); // seed rng
				cloudSpeed[i] = (rand() % 200);

				srand((int)time(0) * i*10);
				float height = (rand() % 150);
				spriteCloud[i].setPosition(-200, height);
				cloudActive[i] = true;
			}
			else
			{
				spriteCloud[i].setPosition(spriteCloud[i].getPosition().x + (cloudSpeed[i] * dt.asSeconds()), spriteCloud[i].getPosition().y);
				// Has cloud reached right edge of screen?
				if (spriteCloud[i].getPosition().x > 1300)
				{
					cloudActive[i] = false;
				}
			}

		}

		/*
		* Draw Scene
		*/

		// clear previous frame
		window.clear();

		// Draw Game
		window.draw(spriteBackground);
		for (int i = 0; i < 3; i++)
		{

			window.draw(spriteCloud[i]);
		}
		window.draw(spriteTree);
		window.draw(spriteBee);

		// Display Draw
		window.display();

	}
	return 0;
}