#include "DebugGUI.h"

DebugGUI::DebugGUI(ObjectManager* objManager)
{
	this->objManager = objManager;
	cube = new Mesh();
	cube->create(Primitives::Cube);
}

DebugGUI::~DebugGUI()
{
	delete cube;
}

void DebugGUI::Render()
{
	// feed inputs to dear imgui, start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Start of gui window
	ImGui::Begin("Create Cube");

	if (ImGui::Button("Create"))
	{
		objManager->Create("New Object: " + std::to_string(currentCubeIndex), cube, 1, 1, glm::vec3(0, currentCubeIndex, 0));
		currentGameObject = objManager->objects.back();
		currentCubeIndex++;
		objManager->SetNamesVector();
		names = objManager->GetNameVector();
	}

	ImGui::SliderFloat("X: ", &currentPOS.x, -100.0f, 100.0f);
	ImGui::SliderFloat("Y: ", &currentPOS.y, -100.0f, 100.0f);
	ImGui::SliderFloat("Z: ", &currentPOS.z, -100.0f, 100.0f);

	if (currentGameObject != nullptr)
		currentGameObject->SetPos(currentPOS);

	ImGui::ListBox("Objects", &currentName, names.data(), names.size());

	// End of gui window
	ImGui::End();

	// Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void DebugGUI::FirstFrame()
{
	objManager->SetNamesVector();
	names = objManager->GetNameVector();
}
