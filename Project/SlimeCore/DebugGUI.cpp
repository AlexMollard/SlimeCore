#include "DebugGUI.h"

DebugGUI::DebugGUI(ObjectManager* objManager, MeshManager* meshManager)
{
	this->objManager = objManager;
	this->meshManager = meshManager;
	this->matManager = objManager->matManager;
}

DebugGUI::~DebugGUI()
{
	delete staticBool;
	delete shadowCastBool;
	delete shininess;
}

void DebugGUI::Render()
{
	// feed inputs to dear imgui, start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ObjectGUI();
	MaterialGUI();

	// Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DebugGUI::FirstFrame()
{
	objManager->SetNamesVector();

	staticBool = new bool();
	shadowCastBool = new bool();

	objNameCharP = &objName[0];
	matNameCharP = &matName[0];

	diffuseList = objManager->textureManager->GetNameList(TEXTURETYPE::Diffuse);
	currentDiffuse = diffuseList[0].c_str();

	specularList = objManager->textureManager->GetNameList(TEXTURETYPE::Specular);
	currentSpecular = specularList[0].c_str();

	normalList = objManager->textureManager->GetNameList(TEXTURETYPE::Normal);
	currentNormal = normalList[0].c_str();

	ambientList = objManager->textureManager->GetNameList(TEXTURETYPE::Ambient);
	currentAmbient = ambientList[0].c_str();

	meshList = meshManager->GetNames();
	currentMesh = meshList[1].c_str();

	materialList = matManager->GetNames();
	currentMaterial = materialList[0].c_str();
}

void DebugGUI::MaterialGUI()
{
	ImGui::Begin("Create Material");
	ImGui::InputText("Name", matNameCharP, sizeof(char) * 32);

	//Diffuse
	ImGui::Image((void*)(intptr_t)objManager->textureManager->Get(objManager->textureManager->GetTextureIndex(currentDiffuse, TEXTURETYPE::Diffuse), TEXTURETYPE::Diffuse)->textureID, ImVec2(150, 150));
	ImGui::SameLine(160.0f);
	ImGui::Text("Diffuse: ");
	ImGui::SameLine(240.0f);
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
	ImGui::SameLine(240.0f);
	ImGui::PushItemWidth(150.0f);
	if (ImGui::BeginCombo("##SpecularTexture", currentSpecular))
	{
		for (int n = 0; n < specularList.size(); n++)
		{
			bool is_selected = (currentSpecular == specularList[n].c_str());
			if (ImGui::Selectable(specularList[n].c_str(), is_selected))
				currentSpecular = specularList[n].c_str();
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	// Normal
	ImGui::Image((void*)(intptr_t)objManager->textureManager->Get(objManager->textureManager->GetTextureIndex(currentNormal, TEXTURETYPE::Normal), TEXTURETYPE::Normal)->textureID, ImVec2(150, 150));
	ImGui::SameLine(160.0f);
	ImGui::Text("Normal: ");
	ImGui::SameLine(240.0f);
	ImGui::PushItemWidth(150.0f);
	if (ImGui::BeginCombo("##NormalTexture", currentNormal))
	{
		for (int n = 0; n < normalList.size(); n++)
		{
			bool is_selected = (currentNormal == normalList[n].c_str());
			if (ImGui::Selectable(normalList[n].c_str(), is_selected))
				currentNormal = normalList[n].c_str();
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	// Ambient
	ImGui::Image((void*)(intptr_t)objManager->textureManager->Get(objManager->textureManager->GetTextureIndex(currentAmbient, TEXTURETYPE::Ambient), TEXTURETYPE::Ambient)->textureID, ImVec2(150, 150));
	ImGui::SameLine(160.0f);
	ImGui::Text("Ambient: ");
	ImGui::SameLine(240.0f);
	ImGui::PushItemWidth(150.0f);
	if (ImGui::BeginCombo("##AmbientTexture", currentAmbient))
	{
		for (int n = 0; n < ambientList.size(); n++)
		{
			bool is_selected = (currentAmbient == ambientList[n].c_str());
			if (ImGui::Selectable(ambientList[n].c_str(), is_selected))
				currentAmbient = ambientList[n].c_str();
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	ImGui::InputFloat("Shininess", shininess);
	ImGui::InputFloat3("Ambient Color", ambColor, 2);
	ImGui::InputFloat3("Diffuse Color", difColor, 2);
	ImGui::InputFloat3("Specular Color", specColor, 2);

	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::SameLine(100.0f);
	if (ImGui::Button("CREATE", ImVec2(200, 50)))
	{
		matManager->Create(
			matName,
			*shininess,
			glm::vec3(ambColor[0], ambColor[1], ambColor[2]),
			glm::vec3(difColor[0], difColor[1], difColor[2]),
			glm::vec3(specColor[0], specColor[1], specColor[2]),
			std::string(currentDiffuse),
			std::string(currentSpecular),
			std::string(currentNormal),
			std::string(currentAmbient)
		);
		materialList = matManager->GetNames();

		currentMaterial = materialList.back().c_str();
	}
	ImGui::End();

}

void DebugGUI::ObjectGUI()
{
	ImGui::Begin("Create Object");

	ImGui::InputText("Name", objNameCharP, sizeof(char) * 32);
	ImGui::Checkbox("Static", staticBool);
	ImGui::SameLine(100.0f);
	ImGui::Checkbox("Cast-Shadow", shadowCastBool);

	//Transform
	ImGui::Text("Transform");
	ImGui::Separator();
	ImGui::InputFloat3("Position", pos, 2);
	ImGui::InputFloat4("Rotation", rot, 2);
	ImGui::InputFloat3("Scale", scale, 2);

	//Mesh
	ImGui::Separator();
	ImGui::Text("Mesh");
	ImGui::SameLine(125.0f);
	ImGui::PushItemWidth(150.0f);
	if (ImGui::BeginCombo("##Mesh", currentMesh))
	{
		for (int n = 0; n < meshList.size(); n++)
		{
			bool is_selected = (currentMesh == meshList[n].c_str());
			if (ImGui::Selectable(meshList[n].c_str(), is_selected))
				currentMesh = meshList[n].c_str();
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	//Material
	ImGui::Separator();
	ImGui::Text("Material");
	ImGui::SameLine(125.0f);
	ImGui::PushItemWidth(150.0f);
	if (ImGui::BeginCombo("##Material", currentMaterial))
	{
		for (int n = 0; n < materialList.size(); n++)
		{
			bool is_selected = (currentMaterial == materialList[n].c_str());
			if (ImGui::Selectable(materialList[n].c_str(), is_selected))
				currentMaterial = materialList[n].c_str();
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::SameLine(100.0f);
	if (ImGui::Button("CREATE", ImVec2(200, 50)))
	{
		objManager->Create(
			objName,
			staticBool,
			glm::vec3(pos[0], pos[1], pos[2]),
			glm::vec4(rot[0], rot[1], rot[2], rot[3]),
			glm::vec3(scale[0], scale[1], scale[2]),
			std::string(currentMesh),
			currentMaterial
		);

	}
	ImGui::End();

}
