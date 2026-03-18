#ifndef _GAME_H_
#define _GAME_H_

#include <GameBase.hpp>
#include <Core/OSDef.hpp>

class SLEAK_API Game : public Sleak::GameBase {
public:
  Game();
  Game(Game &&) = delete;
  Game(const Game &) = default;
  ~Game();

  Game &operator=(Game &&) = delete;
  Game &operator=(const Game &) = delete;

  bool Initialize() override;
  void Begin() override;
  void Loop(float DeltaTime) override;

  int Run();

  inline bool GetIsGameRunning() { return bIsGameRunning; }

private:
  bool bIsGameRunning = true;
};

#endif
