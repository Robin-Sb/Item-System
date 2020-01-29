#include "Inventory.h"

Inventory::Inventory() {
	std::vector<Item> oldItems = ItemPersistence::deserializeInventory();
	items = oldItems;
}

std::vector<Item> Inventory::get_all_items() {
	return items;
}

Item Inventory::get_item(int position) {
	return items.at(position);
}

void Inventory::delete_item(int position) {
	if (position >= items.size()) {
		printf("You don't have an item in that slot! \n");
		return; 
	}
	items.erase(items.begin() + position);
	ItemPersistence::serializeInventory(items);
}

void Inventory::add_item(Item item) {
	int item_size = items.size();
	if (item_size <= 7) {
		items.push_back(item);
		ItemPersistence::serializeInventory(items);
		printf("Item was added to inventory.");
		printf("Current inventory: \n");
		for (int i = 0; i < items.size(); i++) {
			cout << items[i].name << "\n";
		}
	}
	else {
		printf("You can't carry any more items.");
	}
}

void Inventory::item_keyboard_handler() {
		Item item = Item{ "item 1" };
		add_item(item);
}
