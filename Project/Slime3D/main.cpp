#include "Application.h"

int main()
{
	// Check for Memory Leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Application* app = new Application();

	GameObject* gm = new GameObject();
	float count = 0.0f;
	while (true)
	{
		count += 0.5f;
		gm->SetPos(glm::vec3(glm::cos(0.5f * count), glm::sin(0.5f * count), 0));
		gm->Draw(&app->projectionViewMat);
		app->Update();
	}
}