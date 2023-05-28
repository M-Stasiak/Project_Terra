#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <vector>

using namespace sf;
using namespace std;

class Background
{
private:
	vector<Texture*> background_layers_textures;
	vector<vector<Sprite*>> background_layers;
	
	void initTextures();
	void initSprites();
public:
	Background();
	void Render(RenderWindow& gameWindow);
};

