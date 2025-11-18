#include "../include/bittern.h"
#include "../include/bear.h"
#include "../include/desman.h"
#include "../include/npc.h"

Bittern::Bittern(std::string& name, int x, int y) : NPC(BitternType, name, x, y) {}
Bittern::Bittern(std::istream &is) : NPC(BitternType, is) {}

void Bittern::print()
{
    std::cout << *this;
}

bool Bittern::accept(std::shared_ptr<NPC> attacker)
{
    FightVisitor visitor(attacker);
    return visitor.visit(std::make_shared<Bittern>(*this));
}

void Bittern::save(std::ostream &os)
{
    os << "bittern ";
    NPC::save(os);
}

bool Bittern::fight(std::shared_ptr<Desman> other)
{
    fight_notify(other, false);
    return false;
}

bool Bittern::fight(std::shared_ptr<Bittern> other)
{
    fight_notify(other, false);
    return false;
}

bool Bittern::fight(std::shared_ptr<Bear> other)
{
    fight_notify(other, false);
    return false;
}

std::ostream &operator<<(std::ostream &os, Bittern &bittern)
{
    os << "bittern: " << *static_cast<NPC *>(&bittern) << std::endl;
    return os;
}