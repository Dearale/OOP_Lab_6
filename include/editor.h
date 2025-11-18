#ifndef EDITOR__H
#define EDITOR__H
#include "npc.h"
#include <memory>


void initialize_editor();

// Фабрики -----------------------------------
std::shared_ptr<NPC> factory(std::istream &is);
std::shared_ptr<NPC> factory(NpcType type, std::string& name, int x, int y);

// save array to file
void save(const set_t &array, const std::string &filename);

//load array from file
set_t load(const std::string &filename);

// print to screen
std::ostream &operator<<(std::ostream &os, const set_t &array);

set_t fight(const set_t &array, size_t distance);

//printing npcs
void print_npcs(const set_t &array);

void simulate_fight(set_t &array, size_t max_fight_distance);

//generating npcs
void generate_npcs(set_t &array, size_t count, size_t field_size);

#endif // EDITOR__H