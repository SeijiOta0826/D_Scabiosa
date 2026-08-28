#include "ObjectManager.h"

#include "GameObject.h"

void ObjectManager::Initialize() {

}

void ObjectManager::Finalize() {

}

void ObjectManager::Update(float _deltaTime) {
    for (auto& object : mObjects) {
        object->Update(_deltaTime);
    }

    RemoveDestroyObjects();
}

void ObjectManager::Draw() {
    for (auto& object : mObjects) {
        object->Draw();
    }
}

void ObjectManager::RemoveDestroyObjects() {
    std::erase_if(
        mObjects,
        [](const auto& object) {
        return object->IsDestroy();
    }
    );
}

void ObjectManager::Clear() {
    mObjects.clear();
}