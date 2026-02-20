// Copyright (c) 2023-2023 the rbfx project.
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT> or the accompanying LICENSE file.

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/EngineDefs.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Viewport.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include "Urho3D/Engine/StateManager.h"

#include <Core.SamplePlugin/SampleComponent.h>

using namespace Urho3D;

class game: public Application
{
    // Enable type information.
    URHO3D_OBJECT(game, Application);

public:
    /// Construct.
    explicit game(Context* context);

    /// Setup before engine initialization. Modifies the engine parameters.
    void Setup() override;
    /// Setup after engine initialization. Creates the logo, console & debug HUD.
    void Start() override;
    /// Cleanup after the main loop. Called by Application.
    void Stop() override;

private:
    /// Update event handler.
    void Update(VariantMap& eventData);

    /// Scene to be rendered.
    SharedPtr<Scene> scene_;
    /// Viewport that renders the scene.
    SharedPtr<Viewport> viewport_;

    /// Geometry in the scene.
    WeakPtr<Node> geometryNode_;
    SharedPtr<Node> node_;
    SharedPtr<Node> cameraNode_;
};

// Define entry point.
URHO3D_DEFINE_APPLICATION_MAIN(game);

game::game(Context *context) : Application(context)
{

}

//LoadLibrary

void game::Setup()
{
    // Organization and application names are used to create writeable folder in OS-specific location.
    // For example, on Windows it would be C:/Users/<username>/AppData/Roaming/<orgname>/<appname>
    engineParameters_[EP_ORGANIZATION_NAME] = "My Organization";
    engineParameters_[EP_APPLICATION_NAME] = "My Application";
    // conf:// directory is mapped to that writeable folder.
    engineParameters_[EP_LOG_NAME] = "conf://MyApplication.log";
    engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";..;../..";

}

void game::Start()
{
    //SampleComponent::RegisterObject(context_);

    //auto cache = GetSubsystem<ResourceCache>();
    //auto renderer = GetSubsystem<Renderer>();
    scene_ = MakeShared<Scene>(context_);
    scene_->LoadFile("Scenes/Data/Scenes/Default.scene");
    uint32_t num = scene_->GetNumChildren();

    ea::vector<Node*> nodeVec = scene_->GetChildrenWithTag("0x0001", false);
    
    //node_ = scene_->FindChild("Sample Cube");
    num = node_->GetIndexInParent();
    //eastl::string info = node_->GetCategory();
    //eastl::string info1 = node_->GetCategory();
    //eastl::string info2 = node_->GetCategory();
    //Camera* camera = 

    //no
    //const ea::vector<SharedPtr<Node> >& GetChildren()

       // eastl::GetChildren();

    //actorNode_ = scene_->FindChild("Actor");
    
    Camera* camera = node_->FindComponent<Camera>();
    if (!camera)    return;
    cameraNode_ = camera->GetNode();

    //auto player = actorNode_->CreateComponent<PlayerController>();
    //const auto controller = cameraNode_->CreateComponent<FreeFlyController>();
    //controller->SetSpeed(0.0f);
    //controller->SetAcceleratedSpeed(0.0f);

    // Create viewport.
    const auto viewport = MakeShared<Viewport>(context_, scene_, camera);
    //SetViewport(0, viewport);
}

void game::Stop()
{

}

void game::Update(VariantMap& eventData)
{
    auto input = GetSubsystem<Input>();
    if (input->GetKeyPress(KEY_ESCAPE))
        SendEvent(E_EXITREQUESTED);
}
