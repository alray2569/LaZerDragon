// LaZerDragon
// char *args[]
// Gareth Solbeck
// IMGD 3000

// Component count view object

// Engine includes
#include "EventMouse.h"
#include "WorldManager.h"

// Game includes
#include "ComponentCount.h"
#include "Mirror.h"
#include "ldutil.h"


ComponentCount::ComponentCount(std::string type, int initial_count) {
  setComponentType(type);

  setValue(initial_count);
  registerInterest(df::MOUSE_EVENT);
}

std::string ComponentCount::getComponentType() {
  return getViewString();
}

void ComponentCount::setComponentType( std::string type ) {
  // TODO: handle uppercase vs. lowercase
  setViewString(type);
}

int ComponentCount::eventHandler(const df::Event* evt) {
  if (evt->getType() == df::MOUSE_EVENT) {
    const df::EventMouse* mouse = static_cast< const df::EventMouse* > (evt);
    if (mouse->getMouseAction() == df::CLICKED) {
      df::Position grid_pos = snapPosToGrid(mouse->getMousePosition());
      if (mouse->getMouseButton() == df::Mouse::LEFT) {
        leftClick(grid_pos);
        return 1;
      } else if (mouse->getMouseButton() == df::Mouse::RIGHT) {
        rightClick(grid_pos);
        return 1;
      }
    }
  }
  return ViewObject::eventHandler(evt);
}

void ComponentCount::leftClick(df::Position pos) {
  df::ObjectList obj_list = df::WorldManager::getInstance()
      .objectsAtPosition(pos);
  bool occupied = false;
  df::ObjectListIterator iter(&obj_list);

  for (iter.first(); !iter.isDone(); iter.next()) {
    Component* comp = dynamic_cast<Component*>(iter.currentObject());
    // If the object is a component, the space is occupied
    if (comp) {
      occupied = true;
      // If the component is of this type, rotate it
      if (comp->getType() == getComponentType()) {
        comp->rotate();
      }
    }
  }
  // If the position is not occupied and there are components left
  if (!occupied && getValue()) {
    // Try to place a component
    if (placeComponent(pos)) {
      // If successful, decrement the number of components left
      setValue(getValue() - 1);
    }
  }
}

void ComponentCount::rightClick(df::Position pos) {
  df::WorldManager& world_manager = df::WorldManager::getInstance();
  df::ObjectList obj_list = df::WorldManager::getInstance()
      .objectsAtPosition(pos);
  df::ObjectListIterator iter(&obj_list);

  for (iter.first(); !iter.isDone(); iter.next()) {
    Component* comp = dynamic_cast<Component*>(iter.currentObject());
    // If the object is a component of this type, delete it and increment
    if (comp && comp->getType() == getComponentType()) {
      world_manager.markForDelete(comp);
      setValue(getValue() + 1);
    }
  }
}

// Returns true if component was placed successfully
bool ComponentCount::placeComponent(df::Position pos) {
  std::string component_type = getComponentType();
  Component* component;
  if (component_type == "mirror") {
    component = new Mirror();
  } else {
    DF_LOG("ComponentCount::placeComponent(): Invalid component type");
    return false;
  }
  component->setPosition(pos);
  return true;
}
