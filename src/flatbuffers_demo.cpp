//
// Created by zgd on 2023/1/7.
//
#include <iostream>
#include "monster_generated.h"

using namespace std;
using namespace MyGame::Sample;

void SerializeMonster(uint8_t *&buf, int &size) {
  // 创建flatbuffer的建造器，设置初始大小为1024，后续自动按需扩容
  flatbuffers::FlatBufferBuilder builder(1024);

  // 创建各字段
  auto weapon_one_name = builder.CreateString("Sword");
  short weapon_one_damage = 3;

  auto weapon_two_name = builder.CreateString("Axe");
  short weapon_two_damage = 5;

  auto sword = CreateWeapon(builder, weapon_one_name, weapon_one_damage);
  auto axe = CreateWeapon(builder, weapon_two_name, weapon_two_damage);

  auto name = builder.CreateString("Orc");
  unsigned char treasure[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto inventory = builder.CreateVector(treasure, 10);

  std::vector<flatbuffers::Offset<Weapon>> weapon_vector;
  weapon_vector.push_back(sword);
  weapon_vector.push_back(axe);
  auto weapons = builder.CreateVector(weapon_vector);

  Vec3 points[] = {Vec3(1.0f, 2.0f, 3.0f), Vec3(4.0f, 5.0f, 6.0f)};
  auto path = builder.CreateVectorOfStructs(points, 2);

  auto position = Vec3(1.0f, 2.0f, 3.0f);

  int hp = 300;
  int mana = 150;

  // 第一种方式：设置Monster的所有字段
//  auto orc = CreateMonster(builder, &position, mana, hp, name,
//                           inventory, Color_Red, weapons,
//                           Equipment_Weapon, axe.Union(), path);

  // 第二种方式：按需设置Monster的指定字段，未设置的字段保持默认值
  MonsterBuilder monster_builder(builder);
  monster_builder.add_pos(&position);
  monster_builder.add_hp(hp);
  monster_builder.add_name(name);
  monster_builder.add_mana(mana);
  monster_builder.add_inventory(inventory);
  monster_builder.add_color(Color_Red);
  monster_builder.add_weapons(weapons);
  monster_builder.add_equipped_type(Equipment_Weapon);
  monster_builder.add_equipped(axe.Union());
  monster_builder.add_path(path);
  auto orc = monster_builder.Finish();

  // 调用Finish()表明monster已经构建完毕
  builder.Finish(orc);

  // 获取序列化后的buffer，这个操作必须在Finish()之后
  buf = builder.GetBufferPointer();
  size = builder.GetSize();
}

void DeserializeMonster(const uint8_t *buf) {
  auto monster = GetMonster(buf);

  auto pos = monster->pos();
  auto hp = monster->hp();
  auto name = monster->name();
  auto mana = monster->mana();
  auto inventory = monster->inventory();
  auto color = monster->color();
  auto weapons = monster->weapons();
  auto equipment_type = monster->equipped_type();
  auto path = monster->path();

  cout << "pos: { x: " << pos->x() << ", y: " << pos->y() << ", z: " << pos->z() << " }" << endl;
  cout << "hp: " << hp << endl;
  cout << "name: " << name->str() << endl;
  cout << "mana: " << mana << endl;

  cout << "inventory: { ";
  for (decltype(inventory->size()) i = 0; i < inventory->size(); i++) {
    cout << static_cast<uint32_t>((*inventory)[i]);
    cout << (i < inventory->size() - 1 ?  ", " : " ");
  }
  cout << "}" << endl;

  cout << "color: " << EnumNameColor(color) << endl;
  cout << "weapons: { ";
  for (decltype(weapons->size()) i = 0; i < weapons->size(); i++) {
    const auto &weapon = (*weapons)[i];
    cout << "{name: " << weapon->name()->str() << ", damage: " << weapon->damage() << "}";
    cout << (i < weapons->size() - 1 ?  ", " : " ");
  }
  cout << "}" << endl;

  cout << "equipment_type: " << EnumNameEquipment(equipment_type) << endl;
  if (equipment_type == MyGame::Sample::Equipment_Weapon) {
    auto equipped_weapon = monster->equipped_as_Weapon();
    cout << "equipped: weapon {name: " << equipped_weapon->name()->str() << ", damage: " << equipped_weapon->damage() << "}";
  }
  cout << "}" << endl;

  cout << "path: {";
  for (decltype(path->size()) i = 0; i < path->size(); i++) {
    const auto &path_elem = (*path)[i];

    cout << "{ pos: x: " << path_elem->x() << ", y: " << path_elem->y() << ", z: " << path_elem->z() << " }";
    cout << (i < path->size() - 1 ?  ", " : " ");
  }
  cout << "}" << endl;
}

int main() {
  uint8_t *buf = nullptr;
  int size = 0;
  SerializeMonster(buf, size);
  cout << "Serialize Monster, buf: " << reinterpret_cast<void *>(buf) << ", size: " << size << endl;

  cout << "Deserialize Monster:" << endl;
  DeserializeMonster(buf);
  return 0;
}
