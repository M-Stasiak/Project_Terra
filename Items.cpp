#include "Items.h"


void prepareItemsMap(std::map<IDs, Item*>& arg1, std::map <IDs, sf::Texture*>& arg2) {
	arg1[IDs::AppleID] = new Apple(arg2);
	arg1[IDs::StickID] = new Stick(arg2);
	arg1[IDs::WoodenSwordID] = new Wooden_Sword(arg2);
	arg1[IDs::StoneSwordID] = new Stone_Sword(arg2);
	arg1[IDs::WoodenPickaxeID] = new Wooden_Pickaxe(arg2);
	arg1[IDs::StonePickaxeID] = new Stone_Pickaxe(arg2);
}

void prepareItemsTextures(std::map<IDs, sf::Texture*>& arg)
{
	sf::Texture* tileset = new sf::Texture;
	tileset->loadFromFile("Textures/itemsSpriteSheet.png");
	arg[IDs::StickID] = tileset;
	arg[IDs::AppleID] = tileset;
	arg[IDs::WoodenSwordID] = tileset;
	arg[IDs::StoneSwordID] = tileset;
	arg[IDs::WoodenPickaxeID] = tileset;
	arg[IDs::StonePickaxeID] = tileset;

}


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
		isCraftingTableRequired = false;
	}
	if (id == IDs::ChestID) {
		craftedQuantity = 1;
		this->itmsRequiredToCraft.emplace_back(IDs::PlankID, 8);
		isCraftingTableRequired = true;
	}
	if (id == IDs::CraftingTableID) {
		craftedQuantity = 1;
		this->itmsRequiredToCraft.emplace_back(IDs::PlankID, 4);
		isCraftingTableRequired = false;
	}
}

//
//Sword::Sword()
//{
//	
//}
//
//void Sword::Update(float elapsed, Entity& entity, vector<Entity*>& entities)
//{
//	setPosition(entity.getPosition().x, entity.getPosition().y);
//	if (entity.getScale().x > 0 and getScale().x < 0) setScale(abs(getScale().x), getScale().y);
//	else if (entity.getScale().x < 0 and getScale().x > 0) setScale((-1) * abs(getScale().x), getScale().y);
//
//	if (isUsing)
//	{
//		for (auto i : entities)
//		{
//			if (entity.getTexture() != i->getTexture())
//				if (this->getGlobalBounds().intersects(i->getGlobalBounds()))
//				{
//					entitiesToTakeDamage.insert(i);
//					if (getScale().x >= 0)
//						i->move(Vector2f(200, 0) * elapsed);
//					else
//						i->move(Vector2f(-200, 0) * elapsed);
//				}
//		}
//		if (getScale().x >= 0)
//		{
//			//cout << getRotation() << endl;
//			if (getRotation() > 70 and getRotation() < 150)
//			{
//				setRotation(0);
//				isUsing = false;
//				for (auto i : entitiesToTakeDamage)
//					i->TakeDamage(attackStrength);
//				entitiesToTakeDamage.clear();
//			}
//			else rotate(500 * elapsed);
//		}
//		else
//		{
//			//cout << getRotation() << endl;
//			if (getRotation() < 290 and getRotation() > 150)
//			{
//				setRotation(0);
//				isUsing = false;
//				for (auto i : entitiesToTakeDamage)
//					i->TakeDamage(attackStrength);
//				entitiesToTakeDamage.clear();
//			}
//			else rotate(-500 * elapsed);
//		}
//	}
//}

//void Sword::Use()
//{
//	if (!isUsing)
//	{
//		if (getScale().x >= 0) setRotation(-100);
//		else setRotation(100);
//		isUsing = true;
//	}
//}

Wooden_Sword::Wooden_Sword(std::map<IDs, sf::Texture*>& arg)
{
	ID = IDs::WoodenSwordID;
	setTexture(*arg[ID]);
	setTextureRect(IntRect(240, 320, -16, 16));
	type = item_type::tool;
	
}

Stone_Sword::Stone_Sword(std::map<IDs, sf::Texture*>& arg)
{
	ID = IDs::StoneSwordID;
	setTexture(*arg[ID]);
	setTextureRect(IntRect(16, 336, -16, 16));

	type = item_type::tool;
	
	
}

//Gold_Sword::Gold_Sword()
//{
//	ID = IDs::GoldenSwordID;
//	Texture* texture = new Texture;
//	texture->loadFromFile("Textures/itemsSpriteSheet.png");
//	setTexture(*texture);
//	setTextureRect(IntRect(32, 336, -16, 16));
//	origin.x = -10; origin.y = 26;
//	type = item_type::tool;
//	attackStrength = 30;
//	isCraftingTableRequired = true;
//}

Stick::Stick(std::map<IDs, sf::Texture*>& arg)
{
	ID = IDs::StickID;
	setTexture(*arg[ID]);
	setTextureRect(IntRect(224, 336, 16, 16));
	isCraftingTableRequired = false;
	type = material;

}

Apple::Apple(std::map<IDs, sf::Texture*>& arg)
{
	ID = IDs::AppleID;
	setTexture(*arg[ID]);
	setTextureRect(IntRect(48, 144, 16, 16));
	isCraftingTableRequired = false;
	type = material;

}

Material_Item::Material_Item(IDs id, map <IDs, sf::Texture*>& arg1, map <IDs, Item*>& arg3, Vector2f pos)
{
	ID = id;
	setTexture(*arg1[ID]);
	setTextureRect(arg3[ID]->getTextureRect());
	setScale(0.5, 0.5);
	setPosition(pos);
	stackingQuantity = 64;
	type = item_type::material;
	if (id == IDs::StickID) {
		craftedQuantity = 2;
		this->itmsRequiredToCraft.emplace_back(IDs::PlankID, 1);
		isCraftingTableRequired = false;
	}
	else if (id == IDs::AppleID) {
		craftedQuantity = 2;
		this->itmsRequiredToCraft.emplace_back(IDs::PlankID, 1);
		isCraftingTableRequired = false;
	}
}


Tool_Item::Tool_Item(IDs id, map<IDs, sf::Texture*>& arg1, map<IDs, Item*>& arg3, Vector2f pos)
{

	ID = id;
	setTexture(*arg1[ID]);
	setTextureRect(arg3[ID]->getTextureRect());
	setScale(0.5, 0.5);
	setPosition(pos);
	origin.x = -10; origin.y = 26;
	stackingQuantity = 1;
	type = item_type::tool;
	if (id == IDs::WoodenSwordID) {
		craftedQuantity = 1;
		this->itmsRequiredToCraft.emplace_back(IDs::PlankID, 2);
		this->itmsRequiredToCraft.emplace_back(IDs::StickID, 1);
		isCraftingTableRequired = true;
		attackStrength = 10;
	}
	else if (id == IDs::StoneSwordID) {
		craftedQuantity = 1;
		this->itmsRequiredToCraft.emplace_back(IDs::RockID, 2);
		this->itmsRequiredToCraft.emplace_back(IDs::StickID, 1);
		isCraftingTableRequired = true;
		attackStrength = 20;
	}
	else if (id == IDs::WoodenPickaxeID) {
		craftedQuantity = 1;
		this->itmsRequiredToCraft.emplace_back(IDs::PlankID, 3);
		this->itmsRequiredToCraft.emplace_back(IDs::StickID, 1);
		isCraftingTableRequired = true;
		this->blockDamage = 25;
	}
	else if (id == IDs::StonePickaxeID) {
		craftedQuantity = 1;
		this->itmsRequiredToCraft.emplace_back(IDs::RockID, 3);
		this->itmsRequiredToCraft.emplace_back(IDs::StickID, 1);
		isCraftingTableRequired = true;
		this->blockDamage = 50;
	}
}

void Tool_Item::Update(float elapsed, Entity& entity, vector<Entity*>& entities)
{
	setPosition(entity.getPosition().x, entity.getPosition().y);
	if (entity.getScale().x > 0 and getScale().x < 0) setScale(abs(getScale().x), getScale().y);
	else if (entity.getScale().x < 0 and getScale().x > 0) setScale((-1) * abs(getScale().x), getScale().y);

	if (isUsing)
	{
		if (ID == WoodenSwordID || ID == StoneSwordID) {
			for (auto i : entities)
			{
				if (i->getIsAlive())
				{
					if (entity.getTexture() != i->getTexture())
						if (this->getGlobalBounds().intersects(i->getGlobalBounds()))
						{
							i->setState(AnimationName::Damage);
							entitiesToTakeDamage.insert(i);
							if (getScale().x >= 0)
								i->move(Vector2f(200, 0) * elapsed);
							else
								i->move(Vector2f(-200, 0) * elapsed);
						}
				}
			}
			if (getScale().x >= 0)
			{
				//cout << getRotation() << endl;
				if (getRotation() > 70 and getRotation() < 150)
				{
					setRotation(0);
					isUsing = false;
					for (auto i : entitiesToTakeDamage)
						i->TakeDamage(attackStrength);
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
						i->TakeDamage(attackStrength);
					entitiesToTakeDamage.clear();
				}
				else rotate(-500 * elapsed);
			}
		}
		if (ID == WoodenPickaxeID || ID == StonePickaxeID) {
			if (getScale().x >= 0)
			{
				//cout << getRotation() << endl;
				if (getRotation() > 70 and getRotation() < 150)
				{
					setRotation(0);
					isUsing = false;
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
				}
				else rotate(-500 * elapsed);
			}
		}
	}
}

void Tool_Item::Use()
{
	if (!isUsing)
	{
		if (getScale().x >= 0) setRotation(-100);
		else setRotation(100);
		isUsing = true;
	}
}

Wooden_Pickaxe::Wooden_Pickaxe(std::map<IDs, sf::Texture*>& arg)
{
	ID = IDs::WoodenPickaxeID;
	setTexture(*arg[ID]);
	setTextureRect(IntRect(16, 352, -16, 16));
	type = item_type::tool;

}

Stone_Pickaxe::Stone_Pickaxe(std::map<IDs, sf::Texture*>& arg)
{
	ID = IDs::StonePickaxeID;
	setTexture(*arg[ID]);
	setTextureRect(IntRect(32, 352, -16, 16));
	type = item_type::tool;

}
