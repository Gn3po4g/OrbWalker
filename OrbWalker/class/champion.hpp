class Champion : Property {
public:
  AString champion_name();

  std::span<SkinData> skins();
};