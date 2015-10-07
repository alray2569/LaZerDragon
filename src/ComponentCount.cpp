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

      // Left click
      if (mouse->getMouseButton() == df::Mouse::LEFT) {
        df::ObjectList obj_list = df::WorldManager::getInstance()
            .objectsAtPosition(mouse->getMousePosition());
        if (obj_list.isEmpty()) {
          // If there are components still available
          if (getValue() && placeComponent(mouse->getMousePosition())) {
            setValue(getValue() - 1);
          }
        } else {
          df::ObjectListIterator iter(&obj_list);
          for (iter.first(); !iter.isDone(); iter.next()) {
            DF_LOG("Trying to rotate item: %x", iter.currentObject());
            Component* comp = dynamic_cast<Component*>(iter.currentObject());
            if (comp) {
              comp->rotate();
            }
          }
        }
        return 1;
      // Right click
      } else if (mouse->getMouseButton() == df::Mouse::RIGHT) {
        return 1;
      }
    }
  }
  return ViewObject::eventHandler(evt);
}

// Returns true if component was placed successfully
// (To be overridden in subclasses)
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
};
