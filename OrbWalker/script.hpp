#pragma once

namespace script{
enum class Type { AutoKite, CleanLane };

void Init();
void Execute(Type);
}