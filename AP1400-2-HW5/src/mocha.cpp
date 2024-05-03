#include "mocha.h"

Mocha::~Mocha() {
	for (const auto& i : side_items) 
		delete i;
	side_items.clear();
}

Mocha::Mocha() {
	name = "Mocha";
	ingredients.push_back(new Espresso{2});
	ingredients.push_back(new Milk{2});
	ingredients.push_back(new MilkFoam{1});
	ingredients.push_back(new Chocolate{1});
}

std::vector<Ingredient*>& Mocha::get_side_items() {
	return side_items;
}

Mocha::Mocha(Mocha& cap) { 
	name = cap.name;
	for (int i = 0; i < cap.ingredients.size(); i++) {
		ingredients.push_back(create_new_Ing(cap.ingredients[i]));
	}
	for (int i = 0; i < cap.side_items.size(); i++) {
		side_items.push_back(create_new_Ing(cap.side_items[i]));
	}
}

Mocha &Mocha::operator=(Mocha& cap) {
	if (this == &cap) { return *this;}
	name = cap.name;
	
	while (ingredients.size() > 0) {
		ingredients.pop_back();
	}
	while (side_items.size() > 0) {
		side_items.pop_back();
	}
	
	for (int i = 0; i < cap.ingredients.size(); i++) {
		ingredients.push_back(create_new_Ing(cap.ingredients[i]));
	}
	for (int i = 0; i < cap.side_items.size(); i++) {
		side_items.push_back(create_new_Ing(cap.side_items[i]));
	}
	return *this;
}

std::string Mocha::get_name() { return name;}

void Mocha::add_side_item(Ingredient* side) {
	side_items.push_back(side);
}

double Mocha::price() {
	double res = 0.0;
	for (const auto& j : ingredients) 
		res += j->price();
	for (const auto& i : side_items) 
		res += i->price();
	return res;
}
