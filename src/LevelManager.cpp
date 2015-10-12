// LaZerDragon
// char *args[]
// Gareth Solbeck
// IMGD 3000

// Level manager

#include <fstream>
#include <regex>
#include <WorldManager.h>

#include "ldutil.h"
#include "LevelManager.h"

LevelManager::LevelManager() {
  setType("LevelManager");
}

LevelManager& LevelManager::getInstance() {
  static LevelManager instance;
  return instance;
}

int LevelManager::startUp() {
  return Manager::startUp();
}

void LevelManager::shutDown() {
  for (int i = 0; i < MAX_LEVEL; i++) {
    if (level_arr[i]) {
      df::WorldManager::getInstance().markForDelete(level_arr[i]);
    }
  }
  Manager::shutDown();
}

int LevelManager::loadLevel(std::string filename, int level_num) {
  static std::regex level_regex("^[A-Zafjnrvwxyz ]*$");
  std::string level_string, line, title;
  int mirror_count, lens_count, prism_count;

  std::ifstream level_file(filename);

  if (level_file.fail()) {
    DF_LOG("LevelManager::loadLevel(): Error - level file %s failed to open",
        filename.c_str());
    return -1;
  }

  // Get level title
  std::getline(level_file, title);
  // Get component counts
  level_file >> mirror_count >> lens_count >> prism_count;
  if (level_file.fail()) {
    DF_LOG("LevelManager::loadLevel(): Invalid header format");
  }
  level_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  // Get level layout
  int row = 0;
  while( !level_file.eof() ) {
    std::getline(level_file, line);
    if (line.size() != GRID_WIDTH) {
      DF_LOG("LevelManager::loadLevel(): Error on line %d - level is the wrong "
          "width (expected %d characters, found %d characters)", row + 1,
          GRID_WIDTH, line.size());
        level_file.close();
        return -1;
    } else if ( !std::regex_match(line, level_regex) ) {
      for (int i = 0; i < line.size(); i++ ) {
        char temp_str[] = {line[i]};
        if ( !std::regex_match(temp_str, level_regex) ) {
          DF_LOG("LevelManager::loadLevel(): Error on line %d - invalid "
              "character %c", row + 1, line[i]);
          level_file.close();
          return -1;
        }
      }
      DF_LOG("LevelManager::loadLevel(): Error on line %d - invalid characters",
          row + 1);
      level_file.close();
      return -1;
    }
    level_string += line;
    row++;
  }
  if (row != GRID_HEIGHT) {
    DF_LOG("LevelManager::loadLevel(): Error on line %d - level is the wrong "
        "height (expected %d lines, found %d lines)", row, GRID_HEIGHT, row);
    level_file.close();
    return -1;
  }

  Level* new_level = new Level(level_num);
  new_level->setLevelString(level_string);
  new_level->setTitle(title);

  new_level->setCount("mirror", mirror_count);
  new_level->setCount("lens", lens_count);
  new_level->setCount("prism", prism_count);

  level_arr[level_num] = new_level;
  level_file.close();
  return 0;
}

int LevelManager::unloadLevel(int level_num) {
  df::WorldManager::getInstance().markForDelete(level_arr[level_num]);
  level_arr[level_num] = NULL;
  return 0;
}

Level* LevelManager::getLevel(int level_num) const {
  return level_arr[level_num];
}
