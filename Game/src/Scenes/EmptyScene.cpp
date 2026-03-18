#include "Scenes/EmptyScene.hpp"
#include "Core/GameObject.hpp"
#include "ECS/Components/MeshComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/MaterialComponent.hpp"
#include "Math/Vector.hpp"
#include <Lighting/DirectionalLight.hpp>
#include <Lighting/PointLight.hpp>
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

    // --- Material (PBR) ---
    auto* mat = new Sleak::Material();
    mat->SetShader("assets/shaders/default_shader.hlsl");
    mat->SetDiffuseColor((uint8_t)230, (uint8_t)230, (uint8_t)230);
    mat->SetMetallic(0.0f);
    mat->SetRoughness(0.35f);
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

    // --- Sun (key light) ---
    auto* sun = new Sleak::DirectionalLight("Sun");
    sun->SetDirection(Sleak::Math::Vector3D(-0.5f, -0.75f, -0.3f));
    sun->SetColor(1.0f, 0.95f, 0.85f);    // Warm sunlight
    sun->SetIntensity(4.0f);
    AddObject(sun);

    // --- Fill light (simulates sky bounce from opposite side) ---
    auto* fill = new Sleak::DirectionalLight("FillLight");
    fill->SetDirection(Sleak::Math::Vector3D(0.5f, -0.3f, 0.4f));
    fill->SetColor(0.6f, 0.75f, 1.0f);    // Cool sky blue
    fill->SetIntensity(0.8f);
    AddObject(fill);

    // --- Rim/back light (edge definition) ---
    auto* rim = new Sleak::DirectionalLight("RimLight");
    rim->SetDirection(Sleak::Math::Vector3D(0.2f, -0.4f, 0.8f));
    rim->SetColor(1.0f, 0.9f, 0.8f);
    rim->SetIntensity(1.2f);
    AddObject(rim);

    // --- Ambient & atmosphere ---
    auto* lm = GetLightManager();
    if (lm) {
        lm->SetAmbientColor(0.08f, 0.10f, 0.15f);  // Dark blue-ish ambient
        lm->SetAmbientIntensity(0.6f);               // Low — let directional lights do the work
        lm->SetFogColor(0.55f, 0.62f, 0.78f);        // Soft atmospheric haze
        lm->SetFogDistances(40.0f, 100.0f);
        lm->SetFogEnabled(true);
    }

    // --- Camera ---
    Sleak::Math::Vector3D camPos(-5.0f, 3.0f, -5.0f);
    Sleak::Math::Vector3D cubePos(0.0f, 0.0f, 0.0f);
    Sleak::Math::Vector3D forward = (cubePos - camPos).Normalized();

    auto* camera = new Sleak::Camera("MainCamera", camPos, 60.0f, 0.01f, 200.0f);
    camera->SetLookTarget(cubePos);
    camera->AddComponent<Sleak::FreeLookCameraController>();
    camera->Initialize();
    camera->GetComponent<Sleak::FreeLookCameraController>()->SetEnabled(true);

    // Sync FreeLookController yaw/pitch to initial look direction
    auto* controller = camera->GetComponent<Sleak::FreeLookCameraController>();
    if (controller) {
        controller->SetYaw(atan2(forward.GetX(), forward.GetZ()));
        controller->SetPitch(-asin(forward.GetY()));
    }

    AddObject(camera);
    SetActiveCamera(camera);

    Scene::Begin();
}

void EmptyScene::Update(float deltaTime) {
    Scene::Update(deltaTime);
}
