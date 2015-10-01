// LaZerDragon
// Andrew Ray, Gareth Solbeck
// IMGD 3000

// Main game file

// Engine includes
#include "GameManager.h"
#include "LogManager.h"

#define DEBUG true


int main() {
  df::GameManager &game_manager = df::GameManager::getInstance();
  df::LogManager &log_manager = df::LogManager::getInstance();

  if (game_manager.startUp()) {
    log_manager.writeLog("Error starting game manager!");
    game_manager.shutDown();
    return 1; // Error
  }
  log_manager.setFlush(DEBUG);

  df::splash();

  game_manager.shutDown();
  return 0;
}
