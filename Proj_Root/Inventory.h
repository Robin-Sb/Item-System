#pragma once
#include "Item.h"
#include <iostream> 
#include <vector> 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ItemPersistence.h"

class Inventory {
public:
	void item_keyboard_handler();
	void add_item(Item item);
	Item get_item(int position);
	void delete_item(int position);
	std::vector<Item> get_all_items();
	Inventory();
private:
	std::vector<Item> items;
};