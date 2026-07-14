#include "ObjectManager_test.h"

#include "GameObject.h"

void ObjectManager_test::RemoveDestroyObjects() {
    std::erase_if(
        mObjects,
        [](const auto& object) {
        return object->IsDestroy();
    }
    );
}

void ObjectManager_test::Clear() {

}