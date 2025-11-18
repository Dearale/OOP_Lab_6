#pragma once
#include "npc.h"

struct Desman : public NPC
{
    Desman(std::string& name, int x, int y);
    Desman(std::istream &is);

    void print() override;

    bool accept(std::shared_ptr<NPC> attacker) override;
    bool fight(std::shared_ptr<Desman> other) override;
    bool fight(std::shared_ptr<Bittern> other) override;
    bool fight(std::shared_ptr<Bear> other) override;

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Desman &dragon);
};