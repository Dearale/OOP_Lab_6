// Тесты для программы с NPC (Desman, Bittern, Bear)

#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "../include/npc.h"
#include "../include/desman.h"
#include "../include/bittern.h"
#include "../include/bear.h"
#include "../include/editor.h"

// -------------------- NPC base --------------------

TEST(NPCTest, ConstructorAndOutput) {
	std::string name = "Bob";
	Desman d(name, 10, 20);

	EXPECT_EQ(d.type, DesmanType);
	EXPECT_EQ(d.x, 10);
	EXPECT_EQ(d.y, 20);
	EXPECT_EQ(d.name, "Bob");

	std::stringstream ss;
	ss << static_cast<NPC &>(d);
	std::string out = ss.str();
	EXPECT_NE(out.find("name: Bob"), std::string::npos);
	EXPECT_NE(out.find("x:10"), std::string::npos);
	EXPECT_NE(out.find("y:20"), std::string::npos);
}

TEST(NPCTest, StreamConstructorAndSave) {
	std::stringstream in("Alice 3 4");
	Desman d(in);
	EXPECT_EQ(d.name, "Alice");
	EXPECT_EQ(d.x, 3);
	EXPECT_EQ(d.y, 4);

	std::stringstream out;
	d.save(out);
	// формат: "desman Alice 3 4" + перевод строки
	std::string s = out.str();
	EXPECT_NE(s.find("desman"), std::string::npos);
	EXPECT_NE(s.find("Alice"), std::string::npos);
}

TEST(NPCTest, DistanceCheck) {
	std::string n1 = "A";
	std::string n2 = "B";
	Desman a(n1, 0, 0);
	Desman b(n2, 3, 4); // расстояние 5

	auto pa = std::make_shared<Desman>(a);
	auto pb = std::make_shared<Desman>(b);

	EXPECT_TRUE(pa->is_close(pb, 5));
	EXPECT_FALSE(pa->is_close(pb, 4));
}

// -------------------- Fight matrix (accept/fight) --------------------

static std::shared_ptr<Desman> makeDesman(const std::string &name, int x, int y) {
	std::string n = name;
	return std::make_shared<Desman>(n, x, y);
}

static std::shared_ptr<Bittern> makeBittern(const std::string &name, int x, int y) {
	std::string n = name;
	return std::make_shared<Bittern>(n, x, y);
}

static std::shared_ptr<Bear> makeBear(const std::string &name, int x, int y) {
	std::string n = name;
	return std::make_shared<Bear>(n, x, y);
}

TEST(FightLogicTest, DesmanVsOthers) {
	auto d = makeDesman("d", 0, 0);
	auto b = makeBittern("b", 0, 0);
	auto br = makeBear("br", 0, 0);

	// Desman атакует
	EXPECT_FALSE(b->accept(d));   // Bittern vs Desman => false
	EXPECT_TRUE(br->accept(d));   // Bear vs Desman => true (Desman победил медведя)

	// Desman защищается
	EXPECT_FALSE(d->accept(b));   // Desman vs Bittern => false
	EXPECT_TRUE(d->accept(br));   // Desman vs Bear => true
}

TEST(FightLogicTest, BitternVsOthers) {
	auto d = makeDesman("d", 0, 0);
	auto b = makeBittern("b", 0, 0);
	auto br = makeBear("br", 0, 0);

	EXPECT_FALSE(d->accept(b));   // Desman vs Bittern => false
	EXPECT_TRUE(b->accept(br));  // Bittern vs Bear => false
	EXPECT_FALSE(b->accept(d));   // Bittern vs Desman => false
}

TEST(FightLogicTest, BearVsOthers) {
	auto d = makeDesman("d", 0, 0);
	auto b = makeBittern("b", 0, 0);
	auto br = makeBear("br", 0, 0);

	EXPECT_TRUE(d->accept(br));   // Desman vs Bear => true
	EXPECT_TRUE(b->accept(br));   // Bittern vs Bear => false (медведь не побеждает сам себя)
	EXPECT_FALSE(br->accept(br)); // Bear vs Bear => false
}

// -------------------- Editor: factory, save/load, fight --------------------

TEST(EditorTest, FactoryByTypeAndStream) {
	std::string name = "X";
	auto d = factory(DesmanType, name, 1, 2);
	ASSERT_NE(d, nullptr);
	EXPECT_EQ(d->type, DesmanType);

	std::stringstream ss("desman Y 3 4");
	auto from_stream = factory(ss);
	ASSERT_NE(from_stream, nullptr);
	EXPECT_EQ(from_stream->type, DesmanType);
	EXPECT_EQ(from_stream->name, "Y");
}

TEST(EditorTest, SaveAndLoadRoundTrip) {
	set_t s;
	{
		std::string a = "A";
		std::string b = "B";
		s.insert(std::make_shared<Desman>(a, 1, 2));
		s.insert(std::make_shared<Bear>(b, 3, 4));
	}

	const std::string filename = "test_npc_io.txt";
	save(s, filename);

	set_t loaded = load(filename);
	EXPECT_EQ(s.size(), loaded.size());
}

TEST(EditorTest, FightAndSimulateFight) {
	set_t s;
	auto d = makeDesman("D", 0, 0);
	auto br = makeBear("BR", 1, 0); // расстояние 1
	s.insert(d);
	s.insert(br);

	auto dead = fight(s, 5);
	// Desman побеждает Bear согласно Desman::fight(Bear)
	EXPECT_EQ(dead.size(), 2u);
	EXPECT_TRUE(dead.find(br) != dead.end());

	// Проверяем simulate_fight: после одного шага должен остаться только Desman
	simulate_fight(s, 30);
	EXPECT_EQ(s.size(), 0u);
}

TEST(EditorTest, GenerateNPCsProducesNonEmptySet) {
	set_t s;
	generate_npcs(s, 5, 100);
	EXPECT_EQ(s.size(), 5u);
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}