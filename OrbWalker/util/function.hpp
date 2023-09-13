class Object;

namespace function {
  float GameTime();

  bool IsChatOpen();

  bool IsLeagueInBackground();

  bool CanSendInput();

  void PrintMessage(std::string_view, std::string_view);

  INT2 WorldToScreen(FLOAT3 position);

  void AttackObject(Object *target);

  void Move2Mouse();
}// namespace function