#include "Items.h"


Block_Item::Block_Item(map<IDs,Texture*>& arg1, map <IDs, Block*>& arg2, IDs id,Vector2f pos)
{
	ID = id;
	setTexture(*arg1[ID]);
	setTextureRect(arg2[ID]->getTextureRect());
	setScale(0.5, 0.5);
	setPosition(pos);
	stackingQuantity = 64;
	type = item_type::block;
}

Weapon::Weapon()
{
	Texture* texture = new Texture;
	texture->loadFromFile("Textures/itemsSpriteSheet.png");
	setTexture(*texture);
	setTextureRect(IntRect(16, 336, -16, 16));
	origin.x = -10; origin.y = 26;
	setOrigin(origin);
	type = item_type::tool;
	nSteps = 2;
}

void Weapon::Update(float elapsed, Entity& entity, vector<Entity*>& entities)
{
	setPosition(entity.getPosition().x, entity.getPosition().y);
	setScale((entity.getScale().x >= 0 ? 1 : -1) * getScale().x, getScale().y);
	tymczasowa_zmienna = (entity.getScale().x >= 0 ? true : false);

	if (isUsing)
	{
		for (auto i : entities)
		{
			if (entity.getTexture() != i->getTexture())
				if (this->getGlobalBounds().intersects(i->getGlobalBounds()))
					entitiesToTakeDamage.insert(i);
		}
		if (tymczasowa_zmienna)
		{
			//cout << getRotation() << endl;
			if (getRotation() > 70 and getRotation() < 150)
			{
				setRotation(0);
				isUsing = false;
				for (auto i : entitiesToTakeDamage)
					i->TakeDamage(10);
				entitiesToTakeDamage.clear();
			}
			else rotate(500 * elapsed);
		}
		else
		{
			//cout << getRotation() << endl;
			if (getRotation() < 290 and getRotation() > 150)
			{
				setRotation(0);
				isUsing = false;
				for (auto i : entitiesToTakeDamage)
					i->TakeDamage(10);
				entitiesToTakeDamage.clear();
			}
			else rotate(-500 * elapsed);
		}
	}
}

void Weapon::Use()
{
	if (!isUsing)
	{
		if (tymczasowa_zmienna) setRotation(-100);
		else setRotation(100);
		isUsing = true;
	}
}

