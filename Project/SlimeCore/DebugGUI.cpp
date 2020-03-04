#include "DebugGUI.h"

DebugGUI::DebugGUI(ObjectManager* objManager, MeshManager* meshManager)
{
	this->objManager = objManager;
	this->meshManager = meshManager;
	this->matManager = objManager->matManager;
	this->shaderManager = objManager->shaderManager;
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
	for (int i = 0; i < 30; i++)
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

	shaderList = shaderManager->GetNames();
	currentShaderName = shaderList[0].c_str();
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
	
	ImVec2 materialImageSize = ImVec2(100,100);
	float optionsOffSet = 120.0f;

	//Diffuse
	ImGui::Image((void*)(intptr_t)objManager->textureManager->Get(objManager->textureManager->GetTextureIndex(currentDiffuse, TEXTURETYPE::Diffuse), TEXTURETYPE::Diffuse)->textureID, materialImageSize);
	ImGui::SameLine(optionsOffSet);
	ImGui::BeginGroup();
	ImGui::Text("Diffuse: ");
	ImGui::PushItemWidth(150.0f);
	if (ImGui::BeginCombo("DiffuseTexture", currentDiffuse))
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
	ImGui::SliderFloat("DiffuseStrength", &diffuseStrength, 0, 1);
	ImGui::EndGroup();

	// Specular
	ImGui::Image((void*)(intptr_t)objManager->textureManager->Get(objManager->textureManager->GetTextureIndex(currentSpecular, TEXTURETYPE::Specular), TEXTURETYPE::Specular)->textureID, materialImageSize);
	ImGui::SameLine(optionsOffSet);
	ImGui::BeginGroup();
	ImGui::Text("Specular: ");
	ImGui::PushItemWidth(150.0f);
	if (ImGui::BeginCombo("SpecularTexture", currentSpecular))
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
	ImGui::SliderFloat("SpecularStrength",&specularStrength,0,1);
	ImGui::EndGroup();

	// Normal
	ImGui::Image((void*)(intptr_t)objManager->textureManager->Get(objManager->textureManager->GetTextureIndex(currentNormal, TEXTURETYPE::Normal), TEXTURETYPE::Normal)->textureID, materialImageSize);
	ImGui::SameLine(optionsOffSet);
	ImGui::BeginGroup();
	ImGui::Text("Normal: ");
	ImGui::PushItemWidth(150.0f);
	if (ImGui::BeginCombo("NormalTexture", currentNormal))
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
	ImGui::SliderFloat("NormalStrength", &normalStrength, 0, 1);
	ImGui::EndGroup();


	// Ambient
	ImGui::Image((void*)(intptr_t)objManager->textureManager->Get(objManager->textureManager->GetTextureIndex(currentAmbient, TEXTURETYPE::Ambient), TEXTURETYPE::Ambient)->textureID, materialImageSize);
	ImGui::SameLine(optionsOffSet);
	ImGui::BeginGroup();
	ImGui::Text("Ambient: ");
	ImGui::PushItemWidth(150.0f);
	if (ImGui::BeginCombo("AmbientTexture", currentAmbient))
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
	ImGui::SliderFloat("AmbientStrength", &ambientStrength, 0, 1);
	ImGui::EndGroup();


	// Rough
	ImGui::Image((void*)(intptr_t)objManager->textureManager->Get(objManager->textureManager->GetTextureIndex(currentRough, TEXTURETYPE::Rough), TEXTURETYPE::Rough)->textureID, materialImageSize);
	ImGui::SameLine(optionsOffSet);
	ImGui::BeginGroup();
	ImGui::Text("Rough: ");
	ImGui::PushItemWidth(150.0f);
	if (ImGui::BeginCombo("RoughTexture", currentRough))
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
	ImGui::SliderFloat("RoughStrength", &roughStrength, 0, 1);
	ImGui::EndGroup();


	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::SameLine(100.0f);
	if (ImGui::Button("CREATE", ImVec2(200, 50)))
	{
		// Need to create new material
		matManager->Create(
			matName,
			std::string(currentDiffuse), diffuseStrength,
			std::string(currentSpecular), specularStrength,
			std::string(currentNormal), normalStrength,
			std::string(currentAmbient), ambientStrength,
			std::string(currentRough), roughStrength
		);
		materialList = matManager->GetNames();

		currentMaterial = materialList.back().c_str();
	}
	ImGui::End();

}

void DebugGUI::ProfilerGUI(float deltaTime)
{
	ImGui::Begin("Profiler window", &profilerVisable);

	ImGui::Text("FrameRate: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, currentFPS);

	timerDelay += deltaTime;
	if (timerDelay > 1.0f)
	{
		lines[29] = currentFPS;
			smallest = 10000.0f;
			largest = 0.0f;

		for (int n = 0; n < 29; n++)
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
		largest *= 1.1f;
		currentFPS = fpsTotal / fpsCount;

		timerDelay = 0.0f;
		fpsCount = 0;
		fpsTotal = 0.0f;
	}
	else
	{
		fpsCount++;
		fpsTotal += ImGui::GetIO().Framerate;
	}
	ImGui::PlotLines("FrameRate", lines, 30, 0, (const char*)0, smallest, largest, ImVec2(ImGui::GetWindowWidth() - 1, 100));

	ImGui::End();
}

void DebugGUI::HierarchyGUI()
{
	ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Hierarchy", &hierarchyWindowVisable))
	{
		// left
		ImGui::BeginChild("left pane", ImVec2(300, 0), true);

		if (ImGui::IsMouseHoveringWindow())
		{
			if (ImGui::IsMouseClicked(1))
			{
				ImGui::OpenPopup("HierarchyOptions");
			}
		}
		if (ImGui::BeginPopup("HierarchyOptions"))
		{
			if (ImGui::MenuItem("Duplicate")) {}

			if (ImGui::MenuItem("Delete")) {}

			ImGui::Separator();

			if (ImGui::MenuItem("Create Prefab")) {}

			ImGui::Separator();
			if (ImGui::MenuItem("Create Empty")) 
			{
				objManager->Create(objManager->Get(currentObject));
				objectList = objManager->GetNameVector();
				currentObject = objManager->objects.size() - 1;
			}

			if (ImGui::BeginMenu("3D Object"))
			{
				if (ImGui::MenuItem("Cube")) {};

				if (ImGui::MenuItem("Plane")) {};

				if (ImGui::MenuItem("Cylinder")) {};

				if (ImGui::BeginMenu("Light"))
				{
					if (ImGui::MenuItem("Directional Light")) {}
					if (ImGui::MenuItem("Point Light")) {}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			ImGui::EndPopup();
		}

		for (int i = 0; i < objectList.size(); i++)
		{
			if (objManager->Get(i)->GetParent() == nullptr && objManager->Get(i)->GetChildCount() > 0)
				ShowChildObject(objectList[i].c_str(), i);
			else if (objManager->Get(i)->GetParent() == nullptr)
			{
				ImGui::AlignTextToFramePadding();
				if (ImGui::Selectable(objManager->Get(i)->GetName().c_str(), currentObject == i))
					currentObject = i;
			}
		}
		ImGui::EndChild();
		ImGui::SameLine();

		// right
		ImGui::BeginGroup();
		ImGui::BeginChild("Object view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
		ImGui::Text(std::string(objectList[currentObject]).c_str());
		ImGui::Separator();

		//Setting vars
		objNameCharP = &objectList[currentObject][0];

		glm::vec3 tempPos = objManager->Get(currentObject)->GetPos();
		pos[0] = tempPos.x;
		pos[1] = tempPos.y;
		pos[2] = tempPos.z;
		
		glm::vec3 tempScale = objManager->Get(currentObject)->GetScale();
		scale[0] = tempScale.x;
		scale[1] = tempScale.y;
		scale[2] = tempScale.z;

		if (objManager->Get(currentObject)->GetMaterial() != nullptr)
			currentMaterial = objManager->Get(currentObject)->GetMaterial()->name.c_str();
		
		if (objManager->Get(currentObject)->GetMesh() != nullptr)
			currentMesh = objManager->Get(currentObject)->GetMesh()->name;
		
		if (objManager->Get(currentObject)->GetShader() != nullptr)
			currentShaderName = objManager->Get(currentObject)->GetShader()->name.c_str();



		if (objectList[currentObject] == "SkyBox")
		{
			ImGui::TextColored(ImVec4(1, 0, 0, 1), "You're not allowed to edit this object!");
			ImGui::EndChild();
			ImGui::EndGroup();
			ImGui::End();
			return;
		}

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

		//Material
		ImGui::Separator();
		ImGui::Text("Shader");
		ImGui::SameLine(125.0f);
		ImGui::PushItemWidth(150.0f);
		if (ImGui::BeginCombo("##Shader", currentShaderName))
		{
			for (int n = 0; n < shaderList.size(); n++)
			{
				bool is_selected = (currentShaderName == shaderList[n].c_str());
				if (ImGui::Selectable(shaderList[n].c_str(), is_selected))
					currentShaderName = shaderList[n].c_str();
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

			objManager->SetVars(
				currentObject,
				objNameCharP,
				staticBool,
				glm::vec3(pos[0], pos[1], pos[2]),
				glm::vec4(rot[0], rot[1], rot[2], rot[3]),
				glm::vec3(scale[0], scale[1], scale[2]),
				std::string(currentMesh),
				currentMaterial,
				currentShaderName
			);

		ImGui::EndChild();

		ImGui::EndGroup();
	}
	ImGui::End();
}

void DebugGUI::ShowChildObject(const char* prefix, int uid)
{
	ImGui::PushID(uid);
	ImGui::AlignTextToFramePadding();
	bool node_open = ImGui::TreeNode(objectList[uid].c_str());
	ImGui::NextColumn();
	if (node_open)
	{
		if (objManager->Get(uid)->GetChildCount() <= 0)
			return;
		
		std::string name = "This (" + objectList[uid] + ")";

		if (ImGui::Selectable(name.c_str(), currentObject == objManager->FindIndex(objManager->Get(uid))))
			currentObject = objManager->FindIndex(objManager->Get(uid));

		for (int i = 0; i < objManager->Get(uid)->GetChildCount(); i++)
		{
			if (objManager->Get(uid)->GetChildren()[i]->GetChildCount() > 0)
			{
				ImGui::PushID(i);
				ShowChildObject(objManager->Get(uid)->GetChild(i)->GetName().c_str(), objManager->FindIndex(objManager->Get(uid)->GetChild(i)));
				ImGui::PopID();
			}
			else
			{
				ImGui::PushID(i);
				if (ImGui::Selectable(objManager->Get(uid)->GetChild(i)->GetName().c_str(), currentObject == objManager->FindIndex(objManager->Get(uid)->GetChild(i))))
					currentObject = objManager->FindIndex(objManager->Get(uid)->GetChild(i));
				ImGui::PopID();
			}
		}
		ImGui::TreePop();
	}
	ImGui::PopID();
}