#pragma once
#include "Inventory.h"
#include <vector> 

class ItemPersistence {
public:
	static void serializeInventory(vector<Item> items);
	static vector<Item> deserializeInventory();
private:
};