#include "../include/npc.h"

NPC::NPC(NpcType t, std::string& name, int _x, int _y) : type(t), name(name), x(_x), y(_y) {}
NPC::NPC(NpcType t, std::istream &is) : type(t) {
    is >> name;
    is >> x;
    is >> y;
}

bool FightVisitor::visit(std::shared_ptr<Desman> desman) {
    return attacker->fight(desman);
}

bool FightVisitor::visit(std::shared_ptr<Bittern> bittern) {
    return attacker->fight(bittern);
}

bool FightVisitor::visit(std::shared_ptr<Bear> bear) {
    return attacker->fight(bear);
}

void NPC::subscribe(std::shared_ptr<IFightObserver> observer) {
    observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC> defender, bool win) {
    for (auto &o : observers)
        o->on_fight(shared_from_this(), defender, win);
}

bool NPC::is_close(const std::shared_ptr<NPC> &other, size_t distance) const {
    return pow((x - other->x), 2) + pow((y - other->y), 2) <= distance * distance;
}

void NPC::save(std::ostream &os) {
    os << name << " " << x << " " << y << std::endl;
}

std::ostream &operator<<(std::ostream &os, NPC &npc) {
    os << "name: " << npc.name << " { x:" << npc.x << ", y:" << npc.y << " }";
    return os;
}