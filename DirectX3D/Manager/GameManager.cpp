#include "Framework.h"

#include "Scenes/CubeScene.h"
#include "Scenes/GridScene.h"
#include "Scenes/SphereScene.h"
#include "Scenes/TerrainEditorScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/ModelExportScene.h"
#include "Scenes/ModelRenderScene.h"
#include "Scenes/ModelAnimationScene.h"
#include "Scenes/IntancingScene.h"
#include "Scenes/GameScene.h"
#include "Scenes/BillboardScene.h"

// �ָ��� ��ſ� ����

// ������ ��ã�� ������ ����ؼ� ������ �غ����� �սô�

// ���� �˰������� �̸��� �˻��غ���, � ������ ���� ã�Ƴ����� �⺻ ���̵��, ������
// ���̳� �׸�, �� �� �ڽ� �ִ� �������, �ٸ� ������� �� �� �ְ� �������ּ���.
// �׸��� ī�信 ������ �÷��ּ���.

// * ���ͽ�Ʈ��(���ͽ�Ʈ��) �˰����� , A* (A-Star) �˰�����

GameManager::GameManager()
{
    Create();

    SceneManager::Get()->Create("Grid", new GridScene());
    //SceneManager::Get()->Create("ModelExport", new ModelExportScene());

    //SceneManager::Get()->Create("Cube", new CubeScene());
    //SceneManager::Get()->Create("Sphere", new SphereScene());
    //SceneManager::Get()->Create("Terrain", new TerrainEditorScene());
    //SceneManager::Get()->Create("Collision", new CollisionScene());
    //SceneManager::Get()->Create("ModelRender", new ModelRenderScene());
    //SceneManager::Get()->Create("ModelAnimationScene", new ModelAnimationScene());
    //SceneManager::Get()->Create("Instancing", new IntancingScene());
    //SceneManager::Get()->Create("Game", new GameScene());
    SceneManager::Get()->Create("BillboardScene", new BillboardScene());

    SceneManager::Get()->Add("Grid");
    //SceneManager::Get()->Add("ModelExport");
    //SceneManager::Get()->Add("Collision");
    //SceneManager::Get()->Add("Instancing");
    //SceneManager::Get()->Add("Game");
    SceneManager::Get()->Add("BillboardScene");
}

GameManager::~GameManager()
{
    Delete();
}

void GameManager::Update()
{
    Keyboard::Get()->Update();
    Timer::Get()->Update();    

    SceneManager::Get()->Update();

    Environment::Get()->Update();
}

void GameManager::Render()
{
    SceneManager::Get()->PreRender();
    
    Device::Get()->Clear();
    Font::Get()->GetDC()->BeginDraw();
    
    Environment::Get()->Set();    
    SceneManager::Get()->Render();
    
    Environment::Get()->PostSet();
    SceneManager::Get()->PostRender();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    
    string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
    Font::Get()->RenderText(fps, { 100, WIN_HEIGHT - 10 });
    
    static bool isActive = true;

    if (isActive)
    {
        ImGui::Begin("Inspector", &isActive);
        Environment::Get()->GUIRender();
        SceneManager::Get()->GUIRender();
        ImGui::End();
    }    

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    
    Font::Get()->GetDC()->EndDraw();

    Device::Get()->Present();
}

void GameManager::Create()
{
    Keyboard::Get();
    Timer::Get();
    Device::Get();
    Environment::Get();
    Observer::Get();
    
    Font::Get()->AddColor("White", 1, 1, 1);
    Font::Get()->AddStyle("Default", L"����ǹ��� �־�");
    
    Font::Get()->SetColor("White");
    Font::Get()->SetStyle("Default");

    Texture::Add(L"Textures/Color/White.png");
    
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Delete()
{
    Keyboard::Delete();
    Timer::Delete();
    Device::Delete();
    Shader::Delete();
    Texture::Delete();
    Environment::Delete();    
    Observer::Delete();
    Font::Delete();
    
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    
    ImGui::DestroyContext();
}