// LaZerDragon
// char *args[]
// Gareth Solbeck
// IMGD 3000

// Component count view object

// Engine includes
#include "EventMouse.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes
#include "ComponentCount.h"
#include "Lens.h"
#include "LevelManager.h"
#include "Mirror.h"
#include "Prism.h"
#include "ldutil.h"


ComponentCount::ComponentCount(std::string type, int initial_count) {
  setType("ComponentCount");
  setComponentType(type);
  setSelected(false);
  updateFrameBox();

  setValue(initial_count);
  registerInterest(df::MOUSE_EVENT);
}

std::string ComponentCount::getComponentType() const {
  return getViewString();
}

void ComponentCount::setComponentType( std::string type ) {
  // TODO: handle uppercase vs. lowercase
  setViewString(type);
}

bool ComponentCount::getSelected() const {
  return selected;
}

void ComponentCount::setSelected( bool selected /* = true */ ) {
  this->selected = selected;
  if (selected) {
    setColor(df::YELLOW);
  } else {
    setColor(df::WHITE);
  }
}

int ComponentCount::eventHandler(const df::Event* evt) {
  if (evt->getType() == df::MOUSE_EVENT) {
    const df::EventMouse* mouse = static_cast< const df::EventMouse* > (evt);
    if (mouse->getMouseAction() == df::CLICKED) {
      df::Position pos = mouse->getMousePosition();
      if (mouse->getMouseButton() == df::Mouse::LEFT) {
        leftClick(pos);
        return 1;
      } else if (mouse->getMouseButton() == df::Mouse::RIGHT) {
        rightClick(pos);
        return 1;
      }
    }
  }
  return ViewObject::eventHandler(evt);
}

void ComponentCount::leftClick(df::Position pos) {
  if (boxContainsPosition(updateFrameBox(), pos)) {
    // Get all objects at altitude 4 (should be mostly view objects)
    df::ObjectList viewObjects = df::WorldManager::getInstance().getSceneGraph()
        .visibleObjects(4);
    df::ObjectListIterator iter(&viewObjects);
    for (iter.first(); !iter.isDone(); iter.next()) {
      df::Object* temp_obj = iter.currentObject();
      if (temp_obj->getType() == "ComponentCount") {
        static_cast<ComponentCount *>(temp_obj)->setSelected(false);
      }
    }
    setSelected(true);
    df::ResourceManager::getInstance().getSound("click")->play();
    return; // Prevent typical left click actions
  }

  // If left click was not on ViewObject, try to rotate or place a component
  df::Position grid_pos = snapPosToGrid(pos);

  df::ObjectList obj_list = df::WorldManager::getInstance()
      .objectsAtPosition(grid_pos);
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
        df::ResourceManager::getInstance().getSound("woosh")->play();
      }
    }
  }
  // If the position is not occupied and this ComponentCount is selected and
  //  there are components left
  if (!occupied && getSelected() && getValue()) {
    // Try to place a component
    if (placeComponent(grid_pos)) {
      // If successful, decrement the number of components left
      df::ResourceManager::getInstance().getSound("click")->play();
      setValue(getValue() - 1);
    }
  }
}

void ComponentCount::rightClick(df::Position pos) {
  df::Position grid_pos = snapPosToGrid(pos);

  df::WorldManager& world_manager = df::WorldManager::getInstance();
  df::ObjectList obj_list = df::WorldManager::getInstance()
      .objectsAtPosition(grid_pos);
  df::ObjectListIterator iter(&obj_list);

  for (iter.first(); !iter.isDone(); iter.next()) {
    Component* comp = dynamic_cast<Component*>(iter.currentObject());
    // If the object is a component of this type, delete it and increment
    if (comp && comp->getType() == getComponentType()) {
      LevelManager::getInstance().getActiveLevel()->removeComponent(comp);
      world_manager.markForDelete(comp);
      df::ResourceManager::getInstance().getSound("click")->play();
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
  } else if (component_type == "lens") {
    component = new Lens();
  } else if (component_type == "prism") {
    component = new Prism();
  } else {
    DF_LOG("ComponentCount::placeComponent(): Invalid component type");
    return false;
  }
  component->setPosition(pos);
  LevelManager::getInstance().getActiveLevel()->addComponent(component);
  return true;
}

df::Box ComponentCount::updateFrameBox() {
  if (isModified(df::BORDER)) {
    frameBox.setVertical( getBorder() ? 3 : 1 );
  }
  if (isModified(df::VIEW_STRING)) {
    frameBox.setHorizontal( getViewString().size() + 6 );
  }
  if (isModified(df::LOCATION)) {
    df::Position temp_pos = getPosition();
    temp_pos.setX(temp_pos.getX() - frameBox.getHorizontal() / 2);
    temp_pos.setY(temp_pos.getY() - frameBox.getVertical() / 2);
    frameBox.setCorner(temp_pos);
  }
  serialize(); // Reset modified flags
  return frameBox;
}
