#include "DebugGUI.h"

DebugGUI::DebugGUI(ObjectManager* objManager)
{
	this->objManager = objManager;
}

DebugGUI::~DebugGUI()
{
	delete staticBool;
	delete shadowCastBool;
}

void DebugGUI::Render()
{
	float pos[3] = {0,0,0};
	float rot[4] = {0,0,0,0};
	float scale[3] = {0,0,0};

	// feed inputs to dear imgui, start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Start of gui window
	ImGui::Begin("Create Object");
	ImGui::InputText("Name", cstr, sizeof(char) * 32);
	ImGui::Checkbox("Static", staticBool);
	ImGui::SameLine(100.0f);
	ImGui::Checkbox("Cast-Shadow", shadowCastBool);
	ImGui::Text("Transform");
	ImGui::Separator();
	ImGui::InputFloat3("Position", pos,2);
	ImGui::InputFloat4("Rotation", rot,2);
	ImGui::InputFloat3("Scale", scale,2);
	ImGui::Text("Components");
	ImGui::Separator();

	if (ImGui::BeginCombo("Components", currentComponent))
	{
		for (int n = 0; n < componentList.size(); n++)
		{
			bool is_selected = (currentComponent == componentList[n].c_str());
			if (ImGui::Selectable(componentList[n].c_str(), is_selected))
				currentComponent = componentList[n].c_str();
				if (is_selected)
					ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	if (currentComponent == componentList[0].c_str())
		MeshGUI();
	else if (currentComponent == componentList[1].c_str())
		MaterialGUI();
	else if (currentComponent == componentList[2].c_str())
		ShaderGUI();

	// End of gui window
	ImGui::End();

	// Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DebugGUI::FirstFrame()
{
	objManager->SetNamesVector();

	staticBool = new bool();
	shadowCastBool = new bool();

	cstr = &TextBoxString[0];

	componentList.push_back("Mesh");
	componentList.push_back("Material");
	componentList.push_back("Shader");
	currentComponent = componentList[0].c_str();

	diffuseList = objManager->textureManager->GetNameList(TEXTURETYPE::Diffuse);
	currentDiffuse = diffuseList[0].c_str();

	specularList = objManager->textureManager->GetNameList(TEXTURETYPE::Specular);
	currentSpecular = specularList[0].c_str();
}

void DebugGUI::MeshGUI()
{
}

void DebugGUI::MaterialGUI()
{
	//Diffuse
	ImGui::Image((void*)(intptr_t)objManager->textureManager->Get(objManager->textureManager->GetTextureIndex(currentDiffuse, TEXTURETYPE::Diffuse), TEXTURETYPE::Diffuse)->textureID, ImVec2(150, 150));
	ImGui::SameLine(160.0f);
	ImGui::Text("Diffuse: ");
	ImGui::SameLine(220.0f);
	ImGui::PushItemWidth(150.0f);
	if (ImGui::BeginCombo("##DiffuseTexture", currentDiffuse))
	{
		for (int n = 0; n < diffuseList.size(); n++)
		{
			bool is_selected = (currentDiffuse == diffuseList[n].c_str());
			if (ImGui::Selectable(diffuseList[n].c_str(), is_selected))
				currentDiffuse = diffuseList[n].c_str();
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	// Specular
	ImGui::Image((void*)(intptr_t)objManager->textureManager->Get(objManager->textureManager->GetTextureIndex(currentSpecular, TEXTURETYPE::Specular), TEXTURETYPE::Specular)->textureID, ImVec2(150, 150));
	ImGui::SameLine(160.0f);
	ImGui::Text("Specular: ");
	ImGui::SameLine(220.0f);
	ImGui::PushItemWidth(150.0f);
	if (ImGui::BeginCombo("##SpecularTexture", currentSpecular))
	{
		for (int n = 0; n < diffuseList.size(); n++)
		{
			bool is_selected = (currentSpecular == diffuseList[n].c_str());
			if (ImGui::Selectable(diffuseList[n].c_str(), is_selected))
				currentSpecular = diffuseList[n].c_str();
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
}

void DebugGUI::ShaderGUI()
{
}
