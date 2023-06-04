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
	if (id == IDs::PlankID) {
		craftedQuantity = 4;
		this->itmsRequiredToCraft.emplace_back(IDs::WoodID, 1);

	}
	if (id == IDs::ChestID) {
		craftedQuantity = 1;
		this->itmsRequiredToCraft.emplace_back(IDs::PlankID, 8);

	}
}

Sword::Sword()
{
	
}

void Sword::Update(float elapsed, Entity& entity, vector<Entity*>& entities)
{
	setPosition(entity.getPosition().x, entity.getPosition().y);
	if (entity.getScale().x > 0 and getScale().x < 0) setScale(abs(getScale().x), getScale().y);
	else if (entity.getScale().x < 0 and getScale().x > 0) setScale((-1) * abs(getScale().x), getScale().y);

	if (isUsing)
	{
		for (auto i : entities)
		{
			if (entity.getTexture() != i->getTexture())
				if (this->getGlobalBounds().intersects(i->getGlobalBounds()))
					entitiesToTakeDamage.insert(i);
		}
		if (getScale().x >= 0)
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

void Sword::Use()
{
	if (!isUsing)
	{
		if (getScale().x >= 0) setRotation(-100);
		else setRotation(100);
		isUsing = true;
	}
}

Wooden_Sword::Wooden_Sword()
{
	ID = IDs::WoodenSwordID;
	Texture* texture = new Texture;
	texture->loadFromFile("Textures/itemsSpriteSheet.png");
	setTexture(*texture);
	setTextureRect(IntRect(240, 320, -16, 16));
	origin.x = -10; origin.y = 26;
	type = item_type::tool;
}

Stone_Sword::Stone_Sword()
{
	ID = IDs::StoneSwordID;
	Texture* texture = new Texture;
	texture->loadFromFile("Textures/itemsSpriteSheet.png");
	setTexture(*texture);
	setTextureRect(IntRect(16, 336, -16, 16));
	origin.x = -10; origin.y = 26;
	type = item_type::tool;
}

Gold_Sword::Gold_Sword()
{
	ID = IDs::StoneSwordID;
	Texture* texture = new Texture;
	texture->loadFromFile("Textures/itemsSpriteSheet.png");
	setTexture(*texture);
	setTextureRect(IntRect(32, 336, -16, 16));
	origin.x = -10; origin.y = 26;
	type = item_type::tool;
}

