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

void DebugGUI::Render(float deltaTime)
{
	// feed inputs to dear imgui, start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	MainMenuBar();

	if (objectWindowVisable)
		ObjectGUI();
	
	if (materialWindowVisable)
		MaterialGUI();

	if (profilerVisable)
		ProfilerGUI(deltaTime);

	if (hierarchyWindowVisable)
		HierarchyGUI();

	// Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DebugGUI::FirstFrame()
{
	for (int i = 0; i < 50; i++)
	{
		lines[i] = 0;

	};

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

	roughList = objManager->textureManager->GetNameList(TEXTURETYPE::Rough);
	currentRough = roughList[0].c_str();

	meshList = meshManager->GetNames();
	currentMesh = meshList[1].c_str();

	materialList = matManager->GetNames();
	currentMaterial = materialList[0].c_str();

	objectList = objManager->GetNameVector();
	currentObject = 0;
}

void DebugGUI::MainMenuBar()
{
	ImGui::BeginMainMenuBar();

	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("New Scene", "CTRL+N")) {}
		if (ImGui::MenuItem("Open Scene", "CTRL+O")) {}
		if (ImGui::MenuItem("Save Scene", "CTRL+S")) {}

		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("View"))
	{
		if (ImGui::MenuItem("Profiler", "", profilerVisable))
			profilerVisable = (profilerVisable ? false : true);

		if (ImGui::MenuItem("Hierarchy", "", hierarchyWindowVisable))
			hierarchyWindowVisable = (hierarchyWindowVisable ? false : true);

		if (ImGui::MenuItem("Create GameObject","", objectWindowVisable))
			objectWindowVisable = (objectWindowVisable ? false : true);

		if (ImGui::MenuItem("Create Material","", materialWindowVisable))
			materialWindowVisable = (materialWindowVisable ? false : true);
		
		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();
}

void DebugGUI::MaterialGUI()
{
	ImGui::Begin("Create Material", &materialWindowVisable);
	ImGui::InputText("Name", matNameCharP, sizeof(char) * 32);
	int i = 0;

	//Diffuse
	ImGui::Image((void*)(intptr_t)objManager->textureManager->Get(objManager->textureManager->GetTextureIndex(currentDiffuse, TEXTURETYPE::Diffuse), TEXTURETYPE::Diffuse)->textureID, ImVec2(150, 150));
	ImGui::SameLine(160.0f);
	ImGui::BeginGroup();
	ImGui::Text("Diffuse: ");
	ImGui::PushItemWidth(150.0f);
	if (ImGui::BeginCombo("Texture", currentDiffuse))
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
	ImGui::SliderInt("Strength", &i, 0, 255);
	ImGui::EndGroup();

	// Specular
	ImGui::Image((void*)(intptr_t)objManager->textureManager->Get(objManager->textureManager->GetTextureIndex(currentSpecular, TEXTURETYPE::Specular), TEXTURETYPE::Specular)->textureID, ImVec2(150, 150));
	ImGui::SameLine(160.0f);
	ImGui::BeginGroup();
	ImGui::Text("Specular: ");
	ImGui::PushItemWidth(150.0f);
	if (ImGui::BeginCombo("Texture", currentSpecular))
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
	ImGui::SliderInt("Strength",&i,0,255);
	ImGui::EndGroup();

	// Normal
	ImGui::Image((void*)(intptr_t)objManager->textureManager->Get(objManager->textureManager->GetTextureIndex(currentNormal, TEXTURETYPE::Normal), TEXTURETYPE::Normal)->textureID, ImVec2(150, 150));
	ImGui::SameLine(160.0f);
	ImGui::BeginGroup();
	ImGui::Text("Normal: ");
	ImGui::PushItemWidth(150.0f);
	if (ImGui::BeginCombo("Texture", currentNormal))
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
	ImGui::SliderInt("Strength", &i, 0, 255);

	ImGui::EndGroup();

	// Ambient
	ImGui::Image((void*)(intptr_t)objManager->textureManager->Get(objManager->textureManager->GetTextureIndex(currentAmbient, TEXTURETYPE::Ambient), TEXTURETYPE::Ambient)->textureID, ImVec2(150, 150));
	ImGui::SameLine(160.0f);
	ImGui::BeginGroup();
	ImGui::Text("Ambient: ");
	ImGui::PushItemWidth(150.0f);
	if (ImGui::BeginCombo("Texture", currentAmbient))
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
	ImGui::SliderInt("Strength", &i, 0, 255);

	ImGui::EndGroup();

	// Rough
	ImGui::Image((void*)(intptr_t)objManager->textureManager->Get(objManager->textureManager->GetTextureIndex(currentRough, TEXTURETYPE::Rough), TEXTURETYPE::Rough)->textureID, ImVec2(150, 150));
	ImGui::SameLine(160.0f);
	ImGui::BeginGroup();
	ImGui::Text("Rough: ");
	ImGui::PushItemWidth(150.0f);
	if (ImGui::BeginCombo("Texture", currentRough))
	{
		for (int n = 0; n < roughList.size(); n++)
		{
			bool is_selected = (currentRough == roughList[n].c_str());
			if (ImGui::Selectable(roughList[n].c_str(), is_selected))
				currentRough = roughList[n].c_str();
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	ImGui::SliderInt("Strength", &i, 0, 255);

	ImGui::EndGroup();


	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::SameLine(100.0f);
	if (ImGui::Button("CREATE", ImVec2(200, 50)))
	{
		matManager->Create(
			matName,
			std::string(currentDiffuse),
			std::string(currentSpecular),
			std::string(currentNormal),
			std::string(currentAmbient),
			std::string(currentRough)
		);
		materialList = matManager->GetNames();

		currentMaterial = materialList.back().c_str();
	}
	ImGui::End();

}

void DebugGUI::ObjectGUI()
{
	ImGui::Begin("Create Object", &objectWindowVisable);

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
			objNameCharP,
			staticBool,
			glm::vec3(pos[0], pos[1], pos[2]),
			glm::vec4(rot[0], rot[1], rot[2], rot[3]),
			glm::vec3(scale[0], scale[1], scale[2]),
			std::string(currentMesh),
			currentMaterial
		);

		objectList = objManager->GetNameVector();

	}
	ImGui::End();

}

void DebugGUI::ProfilerGUI(float deltaTime)
{
	ImGui::Begin("Profiler window", &profilerVisable);

	ImGui::Text("FrameRate: %.3f ms/frame (%.1f FPS)",
		1000.0f / ImGui::GetIO().Framerate,
		ImGui::GetIO().Framerate);

	timerDelay += deltaTime;
	if (timerDelay > 1.0f)
	{
		lines[59] = ImGui::GetIO().Framerate;
			smallest = 10000.0f;
			largest = 0.0f;

		for (int n = 0; n < 59; n++)
		{
			lines[n] = lines[n + 1];

			if (lines[n] < smallest)
			{
				smallest = lines[n];
			}
			
			if (lines[n] > largest)
			{
				largest = lines[n];
			}

		}
		timerDelay = 0.0f;
	}

	ImGui::PlotLines("FrameRate", lines, 60, 0, (const char*)0, smallest, largest, ImVec2(ImGui::GetWindowWidth(), 100));

	ImGui::End();
}

void DebugGUI::HierarchyGUI()
{
	ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Hierarchy",&hierarchyWindowVisable))
	{
		// left
		ImGui::BeginChild("left pane", ImVec2(150, 0), true);
		
		if (ImGui::IsMouseHoveringWindow())
		{
			if (ImGui::IsMouseClicked(1))
			{
				ImGui::OpenPopup("HierarchyOptions");
			}
		}
		if (ImGui::BeginPopup("HierarchyOptions"))
		{
			if (ImGui::MenuItem("Duplicate")){}

			if (ImGui::MenuItem("Delete")){}

			ImGui::Separator();
			
			if (ImGui::MenuItem("Create Prefab")){}

			ImGui::Separator();
			if (ImGui::MenuItem("Create Empty")){}

			if (ImGui::BeginMenu("3D Object"))
			{
				if (ImGui::MenuItem("Cube")){};

				if (ImGui::MenuItem("Plane")){};

				if (ImGui::MenuItem("Cylinder")){};

				if (ImGui::BeginMenu("Light"))
				{
					if (ImGui::MenuItem("Directional Light")){}
					if (ImGui::MenuItem("Point Light")) {}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			ImGui::EndPopup();
		}
		
		for (int i = 0; i < objectList.size(); i++)
		{
			if (ImGui::Selectable(objectList[i].c_str(), currentObject == i))
				currentObject = i;
		}
		ImGui::EndChild();
		ImGui::SameLine();

		// right
		ImGui::BeginGroup();
		ImGui::BeginChild("Object view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
		ImGui::Text(std::string(objectList[currentObject]).c_str());
		ImGui::Separator();
		if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
		{
			if (ImGui::BeginTabItem("Description"))
			{
				ImGui::Text("THIS IS A WORK IN PROGESS...");
				ImVec2 imageSize = ImVec2(75,75);
				if (objManager->Get(currentObject)->GetTexture(TEXTURETYPE::Diffuse) != nullptr)
					ImGui::Image((void*)(intptr_t)objManager->Get(currentObject)->GetTexture(TEXTURETYPE::Diffuse)->textureID, imageSize);
				ImGui::SameLine();
				if (objManager->Get(currentObject)->GetTexture(TEXTURETYPE::Specular) != nullptr)
					ImGui::Image((void*)(intptr_t)objManager->Get(currentObject)->GetTexture(TEXTURETYPE::Specular)->textureID, imageSize);
				ImGui::SameLine();
				if (objManager->Get(currentObject)->GetTexture(TEXTURETYPE::Normal) != nullptr)
					ImGui::Image((void*)(intptr_t)objManager->Get(currentObject)->GetTexture(TEXTURETYPE::Normal)->textureID, imageSize);
				ImGui::SameLine();
				if (objManager->Get(currentObject)->GetTexture(TEXTURETYPE::Ambient) != nullptr)
					ImGui::Image((void*)(intptr_t)objManager->Get(currentObject)->GetTexture(TEXTURETYPE::Ambient)->textureID, imageSize);
				ImGui::SameLine();
				if (objManager->Get(currentObject)->GetTexture(TEXTURETYPE::Rough) != nullptr)
					ImGui::Image((void*)(intptr_t)objManager->Get(currentObject)->GetTexture(TEXTURETYPE::Rough)->textureID, imageSize);

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Details"))
			{
				ImGui::Text(objectList[currentObject].c_str());

				glm::vec3 cPos = objManager->Get(currentObject)->GetPos();
				std::string pos[3] = { std::to_string(cPos.x),std::to_string(cPos.y),std::to_string(cPos.z) };
				std::string finalPos = ("x: " + pos[0] + " y: " + pos[1] + " z: " + pos[2]);
				ImGui::Text(finalPos.c_str());

				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::EndChild();

		ImGui::EndGroup();
	}
	ImGui::End();
}
