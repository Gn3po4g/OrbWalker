class Property {
protected:
  template<typename Type>
  inline Type prop(uintptr_t offset) {
    return *reinterpret_cast<Type *>(reinterpret_cast<uintptr_t>(this) + offset);
  }
};