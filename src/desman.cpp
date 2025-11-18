#include "../include/desman.h"
#include "../include/bittern.h"
#include "../include/bear.h"
#include "../include/npc.h"
#include <memory>

Desman::Desman(std::string& name, int x, int y) : NPC(DesmanType, name, x, y) {}
Desman::Desman(std::istream &is) : NPC(DesmanType, is) {}

void Desman::print()
{
    std::cout << *this;
}

bool Desman::accept(std::shared_ptr<NPC> attacker)
{
    FightVisitor visitor(attacker);
    return visitor.visit(std::make_shared<Desman>(*this));
}

bool Desman::fight(std::shared_ptr<Desman> other) 
{
    fight_notify(other, false);
    return false;
}

bool Desman::fight(std::shared_ptr<Bittern> other) 
{
    fight_notify(other, false);
    return false;
}

bool Desman::fight(std::shared_ptr<Bear> other) 
{
    fight_notify(other, true);
    return true;
}

void Desman::save(std::ostream &os) 
{
    os << "desman ";
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Desman &desman)
{
    os << "desman: " << *static_cast<NPC *>(&desman) << std::endl;
    return os;
}