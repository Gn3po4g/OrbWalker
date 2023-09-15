class Object;
class ObjList;

namespace script {
  extern float gameTime;
  extern Object *self;
  extern Object *markedObject;
  extern ObjList* minions;

  void Init();

  void Update();
}// namespace script