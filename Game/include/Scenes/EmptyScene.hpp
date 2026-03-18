#ifndef _EMPTY_SCENE_HPP_
#define _EMPTY_SCENE_HPP_

#include <Core/Scene.hpp>

class EmptyScene : public Sleak::Scene {
public:
    EmptyScene();
    ~EmptyScene() override = default;

    // Resource lifecycle — load/unload assets and scene objects
    void OnLoad() override;
    void OnUnload() override;

    // Activation lifecycle — called when scene becomes active/inactive
    void OnActivate() override;
    void OnDeactivate() override;

    // Called once after the scene is fully initialized
    void Begin() override;

    // Per-frame update
    void Update(float deltaTime) override;
};

#endif // _EMPTY_SCENE_HPP_
