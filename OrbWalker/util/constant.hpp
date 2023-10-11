constexpr auto objIndex = 0x10;
constexpr auto objTeam = 0x3C;
constexpr auto objPosition = 0x220;
constexpr auto objVisible = 0x320;
constexpr auto objMana = 0x350;
constexpr auto objTargetable = 0xEC0;
constexpr auto objHealth = 0x1068;
constexpr auto objSkinId = 0x1244;
constexpr auto objActionState = 0x13D0;
constexpr auto objAttackRange = 0x16C4;
constexpr auto objBuff = 0x27D8;
constexpr auto objManaCost = 0x2A88;
constexpr auto objSpell = 0x30C8;
constexpr auto objCharData = 0x35A0;
constexpr auto objDataStack = 0x35D0;
constexpr auto objName = 0x3868;

enum GameState : int32_t { Loading = 0, Connecting = 1, Running = 2, Paused = 3, Finished = 4, Exiting = 5 };

enum SpellSlot : int32_t {
		SpellSlot_Q,
		SpellSlot_W,
		SpellSlot_E,
		SpellSlot_R,
		SpellSlot_Summoner1,
		SpellSlot_Summoner2,
		SpellSlot_Item1,
		SpellSlot_Item2,
		SpellSlot_Item3,
		SpellSlot_Item4,
		SpellSlot_Item5,
		SpellSlot_Item6,
		SpellSlot_Trinket,
		SpellSlot_Recall,
    SpellSlot_Other,
		//SpellSlot_SpecialAttack = 45,
		//SpellSlot_BasicAttack1 = 64,
		//SpellSlot_BasicAttack2 = 65,
};

enum CharacterState : uint16_t {
  CanAttack = 1 << 0,
  CanMove = 1 << 1,
  CanCast = 1 << 2,
  Immovable = 1 << 3,
  Unknownz = 1 << 4,
  IsStealth = 1 << 5,
  Taunted = 1 << 6,
  Feared = 1 << 7,
  Fleeing = 1 << 8,
  Supressed = 1 << 9,
  Asleep = 1 << 10,
  NearSight = 1 << 11,
  Ghosted = 1 << 12,
  HasGhost = 1 << 13,
  Charmed = 1 << 14,
  NoRender = 1 << 15
};

enum CharacterHash : uint32_t {
  SRU_ChaosMinionMelee = 0xB87BB4C7,
  SRU_ChaosMinionRanged = 0xD86EA814,
  SRU_ChaosMinionSiege = 0x6B0C5C0,
  SRU_ChaosMinionSuper = 0x3A6B38CE,
  SRU_OrderMinionMelee = 0xD11193B9,
  SRU_OrderMinionRanged = 0xC44285A2,
  SRU_OrderMinionSiege = 0x1F46A4B2,
  SRU_OrderMinionSuper = 0x530117C0,
  SRU_Plant_Vision = 0x4D61E805,
  SRU_Plant_Satchel = 0xE8814FF5,
  SRU_Plant_Health = 0xC3479CD9,
  SRU_Gromp = 0xD1C19B7E,
  SRU_Krug = 0xA20205E2,
  SRU_KrugMini = 0xF8123C99,
  SRU_KrugMiniMini = 0xA8245C50,
  SRU_Murkwolf = 0x621947DC,
  SRU_MurkwolfMini = 0x9A1D4493,
  SRU_Razorbeak = 0x244E9932,
  SRU_RazorbeakMini = 0xA2C97FE9,
  SRU_Blue = 0xFC505223,
  SRU_Red = 0x9CA35508,
  Sru_Crab = 0x2DB77AF9,
  SRU_Dragon_Air = 0x11D34E07,
  SRU_Dragon_Earth = 0x606DCD87,
  SRU_Dragon_Fire = 0x99A947D9,
  SRU_Dragon_Water = 0x27F996F4,
  SRU_Dragon_Hextech = 0xA076EECE,
  SRU_Dragon_Chemtech = 0xF956A026,
  SRU_Dragon_Elder = 0x5944E907,
  SRU_RiftHerald = 0xDDAF53D2,
  SRU_Baron = 0x68AC12C9,
  HA_ChaosMinionMelee = 0xD1BBDB04,
  HA_ChaosMinionRanged = 0x35751117,
  HA_ChaosMinionSiege = 0x1FF0EBFD,
  HA_ChaosMinionSuper = 0x53AB5F0B,
  HA_OrderMinionMelee = 0xEA51B9F6,
  HA_OrderMinionRanged = 0x2148EEA5,
  HA_OrderMinionSiege = 0x3886CAEF,
  HA_OrderMinionSuper = 0x6C413DFD,
  JammerDevice = 0x8223B6BA,
  SightWard = 0x7C1BCAD9,
  YellowTrinket = 0x40D7E043,
  BlueTrinket = 0xE20532FD,
};