#include "../include/bear.h"
#include "../include/desman.h"
#include "../include/bittern.h"
#include "../include/npc.h"

Bear::Bear(std::string& name, int x, int y) : NPC(BearType, name, x, y) {}
Bear::Bear(std::istream &is) : NPC(BearType, is) {}
void Bear::print()
{
    std::cout << *this;
}

bool Bear::accept(std::shared_ptr<NPC> attacker) {
    FightVisitor visitor(attacker);
    return visitor.visit(std::make_shared<Bear>(*this));
}

void Bear::save(std::ostream &os)
{
    os << "bear ";
    NPC::save(os);
}

bool Bear::fight(std::shared_ptr<Desman> other)
{
    fight_notify(other, true);
    return true;
}

bool Bear::fight(std::shared_ptr<Bittern> other)
{
    fight_notify(other, true);
    return true;
}

bool Bear::fight(std::shared_ptr<Bear> other)
{
    fight_notify(other, false);
    return false;
}

std::ostream &operator<<(std::ostream &os, Bear &bear)
{
    os << "bear: " << *static_cast<NPC *>(&bear) << std::endl;
    return os;
}