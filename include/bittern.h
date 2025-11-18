#pragma once
#include "npc.h"

struct Bittern : public NPC
{
    Bittern(std::string& name, int x, int y);
    Bittern(std::istream &is);
    void print() override;
    void save(std::ostream &os) override;

    bool accept(std::shared_ptr<NPC> attacker) override;
    bool fight(std::shared_ptr<Desman> other) override;
    bool fight(std::shared_ptr<Bittern> other) override;
    bool fight(std::shared_ptr<Bear> other) override;
    friend std::ostream &operator<<(std::ostream &os, Bittern &knight);
};