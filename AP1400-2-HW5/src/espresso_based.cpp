#include "espresso_based.h"

EspressoBased::~EspressoBased() {
	for (const auto& i : ingredients) 
		delete i;
	ingredients.clear();
}

std::vector<Ingredient*>& EspressoBased::get_ingredients() {
	return ingredients;
}

EspressoBased::EspressoBased(const EspressoBased& esp) : ingredients(esp.ingredients), name(esp.name) { }

void EspressoBased::operator=(const EspressoBased& esp) {
	name = esp.name;
	ingredients = esp.ingredients;
}

void EspressoBased::brew() {
	std::cout << "make successfully" << std::endl;
}

Ingredient *create_new_Ing(Ingredient *&obj) {
	Ingredient *res;
	std::string name = obj->get_name();
	if (name == "Espresso") { res = new Espresso{obj->get_units()};}
	else if (name == "Chocolate") { res = new Chocolate{obj->get_units()};}
	else if (name == "Milk") { res = new Milk{obj->get_units()};}
	else if (name == "MilkFoam") { res = new MilkFoam{obj->get_units()};}
	else if (name == "Cinnamon") { res = new Cinnamon{obj->get_units()};}
	else if (name == "Sugar") { res = new Sugar{obj->get_units()};}
	else if (name == "Water") { res = new Water{obj->get_units()};}
	else if (name == "Cookie") { res = new Cookie{obj->get_units()};}
	return res;
}
