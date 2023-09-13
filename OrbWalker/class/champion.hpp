class Champion : Property {
public:
  AString champion_name();

  std::span<Skin> skins();
};