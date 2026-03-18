#include "Game.hpp"
#include "Scenes/EmptyScene.hpp"
#include <Core/Application.hpp>

Game::Game() {
  bIsGameRunning = true;
}

Game::~Game() {
  SLEAK_LOG("The game has been destroyed. Cleaning up resources...");
}

bool Game::Initialize() {
  Sleak::Application::GetInstance()->SetMSAASampleCount(8);

  // Register scenes
    auto* emptyScene = new EmptyScene();
    AddScene(emptyScene);
    SetActiveScene(emptyScene);

    return true;
}

void Game::Begin() {
}

void Game::Loop(float DeltaTime) {
}

int Game::Run() {
  return EXIT_SUCCESS;
}
