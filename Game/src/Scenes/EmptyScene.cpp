#include "Scenes/EmptyScene.hpp"
#include "Core/GameObject.hpp"
#include "ECS/Components/MeshComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/MaterialComponent.hpp"
#include "Math/Vector.hpp"
#include <Lighting/DirectionalLight.hpp>
#include <Lighting/LightManager.hpp>
#include <Runtime/Material.hpp>
#include <Runtime/Skybox.hpp>
#include <Camera/Camera.hpp>
#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Components/FreeLookCameraController.hpp>
#include <Math/Math.hpp>

EmptyScene::EmptyScene()
    : Scene("EmptyScene") {}

void EmptyScene::OnLoad() {
    Scene::OnLoad();
}

void EmptyScene::OnUnload() {
    Scene::OnUnload();
}

void EmptyScene::OnActivate() {
    Scene::OnActivate();
}

void EmptyScene::OnDeactivate() {
    Scene::OnDeactivate();
}

void EmptyScene::Begin() {

    // --- Material ---
    auto* mat = new Sleak::Material();
    mat->SetShader("assets/shaders/default_shader.hlsl");
    mat->SetDiffuseColor(
        (uint8_t)255, (uint8_t)255, (uint8_t)255);
    mat->SetSpecularColor(
        (uint8_t)255, (uint8_t)255, (uint8_t)255);
    mat->SetShininess(32.0f);
    mat->SetMetallic(0.0f);
    mat->SetRoughness(0.5f);
    mat->SetAO(1.0f);
    mat->SetOpacity(1.0f);
    auto cubeMaterial = Sleak::RefPtr<Sleak::Material>(mat);

    // --- Cube ---
    auto cube = Sleak::GameObject::CreateCube(
        Sleak::Vector3D(0, 0, 0));
    cube->SetTag("Cube");
    cube->AddComponent<Sleak::MaterialComponent>(cubeMaterial);
    AddObject(cube);

    // --- Skybox (6-face cubemap) ---
    // Order: +X (right), -X (left), +Y (top), -Y (bottom), +Z (front), -Z (back)
    auto* skybox = new Sleak::Skybox(std::array<std::string, 6>{
        "assets/skybox/right.jpg",
        "assets/skybox/left.jpg",
        "assets/skybox/top.jpg",
        "assets/skybox/bottom.jpg",
        "assets/skybox/front.jpg",
        "assets/skybox/back.jpg"
    });
    SetSkybox(skybox);

    // --- Directional light (sun) ---
    auto* sun = new Sleak::DirectionalLight("Sun");
    sun->SetDirection(Sleak::Math::Vector3D(-0.4f, -0.8f, -0.4f));
    sun->SetColor(1.0f, 0.98f, 0.95f);
    sun->SetIntensity(5.0f);
    AddObject(sun);

    // --- Ambient lighting ---
    auto* lm = GetLightManager();
    if (lm) {
        lm->SetAmbientColor(0.15f, 0.15f, 0.2f);
        lm->SetAmbientIntensity(1.0f);
    }

    // --- Camera: look at the cube ---
    if (GetDebugCamera()) {
        Sleak::Math::Vector3D camPos(-5.0f, 3.0f, -5.0f);
        Sleak::Math::Vector3D cubePos(0.0f, 0.0f, 0.0f);
        Sleak::Math::Vector3D forward = (cubePos - camPos).Normalized();

        GetDebugCamera()->SetPosition(camPos);
        GetDebugCamera()->SetLookTarget(cubePos);

        // Set the FreeLookController's yaw/pitch to match, otherwise it overrides on first frame
        auto* controller = GetDebugCamera()->GetComponent<Sleak::FreeLookCameraController>();
        if (controller) {
            controller->SetYaw(atan2(forward.GetX(), forward.GetZ()));
            controller->SetPitch(-asin(forward.GetY()));
        }
    }

    Scene::Begin();
}

void EmptyScene::Update(float deltaTime) {
    Scene::Update(deltaTime);
}
