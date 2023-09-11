namespace script {
  extern float gameTime;

  inline Object *LocalPlayer() { return *(Object **)offset::oLocalPlayer; }
  inline ObjList *Heroes() { return *(ObjList **)offset::oHeroList; }
  inline ObjList *Minions() { return *(ObjList **)offset::oMinionList; }
  inline ObjList *Turrets() { return *(ObjList **)offset::oTurretList; }

  void Update();
}// namespace script