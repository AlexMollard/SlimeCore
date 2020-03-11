#include "DebugGUI.h"
#include <random>
#include <Windows.h>
DebugGUI::DebugGUI(ObjectManager* objManager, MeshManager* meshManager, MaterialManager* materialManager, TextureManager* textureManager, ShaderManager* shaderManager)
{
	this->objManager = objManager;
	this->meshManager = meshManager;
	this->matManager = materialManager;
	this->shaderManager = shaderManager;
	this->textureManager = textureManager;
	srand(time(NULL));
}

DebugGUI::~DebugGUI()
{
	delete staticBool;
	delete shadowCastBool;
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

	diffuseList = textureManager->GetNameList(TEXTURETYPE::Albedo);
	currentAlbedo = diffuseList[0].c_str();

	specularList = textureManager->GetNameList(TEXTURETYPE::Specular);
	currentSpecular = specularList[0].c_str();

	normalList = textureManager->GetNameList(TEXTURETYPE::Normal);
	currentNormal = normalList[0].c_str();

	ambientList = textureManager->GetNameList(TEXTURETYPE::Ambient);
	currentAmbient = ambientList[0].c_str();

	roughList = textureManager->GetNameList(TEXTURETYPE::Rough);
	currentRough = roughList[0].c_str();

	displacementList = textureManager->GetNameList(TEXTURETYPE::Displacement);
	currentDisplacement = displacementList[0].c_str();

	meshList = meshManager->GetNames();
	currentMesh = meshList[1].c_str();

	materialList = matManager->GetNames();
	currentMaterial = materialList[0].c_str();
	currentEditorMaterial = materialList[0].c_str();

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

		if (ImGui::MenuItem("Hierarchy", "CTRL+H", hierarchyWindowVisable))
			hierarchyWindowVisable = (hierarchyWindowVisable ? false : true);

		if (ImGui::MenuItem("Create Material","", materialWindowVisable))
			materialWindowVisable = (materialWindowVisable ? false : true);
		
		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();
}

void DebugGUI::MaterialGUI()
{

	ImGui::Begin("Create Material", &materialWindowVisable, ImGuiWindowFlags_NoScrollbar);

	ImVec2 windowSize = ImVec2(ImGui::GetWindowWidth() - 20, ImGui::GetWindowHeight());
	float imageOffset = windowSize.x * 0.33f;
	ImVec2 materialImageSize = ImVec2(imageOffset / 1.75f, imageOffset / 1.75f);
	float optionsOffSet = 120.0f;

	float namePos = (windowSize.x * 0.5f) - imageOffset / 2;
	float randomPos = namePos + (imageOffset * 1.05f);
	float materialselectpos = namePos - imageOffset * 0.55f;
	float childcenter = imageOffset * 0.25f;
	ImVec2 childSize = ImVec2(imageOffset * 0.95f, materialImageSize.y + 100);
	std::string currentValues[6] = { currentAlbedo,currentSpecular,currentNormal,currentAmbient,currentRough,currentDisplacement };
	float currentStrengthValues[6] = { diffuseStrength,specularStrength,normalStrength,ambientStrength,roughStrength,displacementStrength };


	ImGui::SameLine(materialselectpos - 50);
	if (ImGui::Button("+", ImVec2(20, 20)))
	{
		matManager->Create(
			matName,
			std::string(currentAlbedo), diffuseStrength,
			std::string(currentSpecular), specularStrength,
			std::string(currentNormal), normalStrength,
			std::string(currentAmbient), ambientStrength,
			std::string(currentRough), roughStrength,
			std::string(currentDisplacement), displacementStrength
		);
		materialList = matManager->GetNames();

		currentEditorMaterial = materialList.back().c_str();
	}

	ImGui::SameLine(materialselectpos);
	ImGui::PushItemWidth(imageOffset / 2);
	if (ImGui::BeginCombo("##materialSelect", currentEditorMaterial))
	{
		for (int n = 0; n < materialList.size(); n++)
		{
			bool is_selected = (currentEditorMaterial == materialList[n].c_str());
			if (ImGui::Selectable(materialList[n].c_str(), is_selected))
				currentEditorMaterial = materialList[n].c_str();
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();

		// Set material stuff here
		Material* cMaterial = matManager->Get(currentEditorMaterial);

		if (cMaterial != nullptr)
		{
			currentAlbedo = (cMaterial->GetAlbedo() != nullptr) ? cMaterial->GetAlbedo()->GetNameC() : diffuseList[0].c_str();

			currentSpecular = (cMaterial->GetSpecMap() != nullptr) ? cMaterial->GetSpecMap()->GetNameC() : specularList[0].c_str();

			currentNormal = (cMaterial->GetNormalMap() != nullptr) ? cMaterial->GetNormalMap()->GetNameC() : normalList[0].c_str();

			currentAmbient = (cMaterial->GetAmbientMap() != nullptr) ? cMaterial->GetAmbientMap()->GetNameC() : ambientList[0].c_str();

			currentRough = (cMaterial->GetRoughMap() != nullptr) ? cMaterial->GetRoughMap()->GetNameC() : roughList[0].c_str();

			currentDisplacement = (cMaterial->GetDisplacementMap() != nullptr) ? cMaterial->GetDisplacementMap()->GetNameC() : displacementList[0].c_str();
		}
	}

	ImGui::SameLine(materialselectpos - 30);
	if (matManager->GetIndex(matManager->Get(currentEditorMaterial)) >= 4)
		if (ImGui::Button("-", ImVec2(20, 20))) 
	{
		matManager->Remove(matManager->Get(currentEditorMaterial), objManager->Get(0,objManager->GetObjectSize()));
		materialList = matManager->GetNames();
		currentEditorMaterial = materialList[0].c_str();
	}

	ImGui::PushItemWidth(imageOffset);
	ImGui::SameLine(namePos);
	ImGui::InputText("", matNameCharP, sizeof(char) * 64);
	ImGui::SameLine(randomPos);
	if (ImGui::Button("Random", ImVec2(materialImageSize.x, 20)) || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_R) == GLFW_PRESS)
	{
		currentAlbedo = diffuseList[rand() % diffuseList.size()].c_str();
		currentSpecular = specularList[rand() % specularList.size()].c_str();
		currentNormal = normalList[rand() % normalList.size()].c_str();
		currentAmbient = ambientList[rand() % ambientList.size()].c_str();
		currentRough = roughList[rand() % roughList.size()].c_str();
	}

	ImGui::NewLine();

#pragma region Albedo
	//Albedo
	ImGui::BeginChild("Albedo", childSize, false);
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	ImGui::Checkbox("Albedo", staticBool);
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	ImGui::Image((void*)(intptr_t)textureManager->Get(textureManager->GetTextureIndex(currentAlbedo, TEXTURETYPE::Albedo), TEXTURETYPE::Albedo)->GetID(), materialImageSize);
	ImGui::PushItemWidth(materialImageSize.x);
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	if (ImGui::BeginCombo("##diffuseSelect", currentAlbedo))
	{
		for (int n = 0; n < diffuseList.size(); n++)
		{
			bool is_selected = (currentAlbedo == diffuseList[n].c_str());
			if (ImGui::Selectable(diffuseList[n].c_str(), is_selected))
				currentAlbedo = diffuseList[n].c_str();
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	ImGui::PushItemWidth(materialImageSize.x);
	ImGui::SliderFloat("##diffuseStrength", &diffuseStrength, 0, 1);
	ImGui::EndChild();
#pragma endregion

#pragma region Specular
	// Specular
	ImGui::SameLine();
	ImGui::BeginChild("Specular", childSize, false);
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	ImGui::Checkbox("Specular", staticBool);
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	ImGui::Image((void*)(intptr_t)textureManager->Get(textureManager->GetTextureIndex(currentSpecular, TEXTURETYPE::Specular), TEXTURETYPE::Specular)->GetID(), materialImageSize);
	ImGui::PushItemWidth(materialImageSize.x);
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	if (ImGui::BeginCombo("##specularSelect", currentSpecular))
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
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	ImGui::PushItemWidth(materialImageSize.x);
	ImGui::SliderFloat("##specularStrength", &specularStrength, 0, 1);
	ImGui::EndChild();
#pragma endregion
	
#pragma region Normal
	// Normal
	ImGui::SameLine();
	ImGui::BeginChild("Normal", childSize, false);
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	ImGui::Checkbox("Normal", staticBool);
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	ImGui::Image((void*)(intptr_t)textureManager->Get(textureManager->GetTextureIndex(currentNormal, TEXTURETYPE::Normal), TEXTURETYPE::Normal)->GetID(), materialImageSize);
	ImGui::PushItemWidth(materialImageSize.x);
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	if (ImGui::BeginCombo("##normalSelect", currentNormal))
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
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	ImGui::PushItemWidth(materialImageSize.x);
	ImGui::SliderFloat("##normalStrength", &normalStrength, 0, 10);
	ImGui::EndChild();
#pragma endregion

#pragma region Ambient
	// Ambient
	ImGui::NewLine();
	ImGui::BeginChild("Ambient", childSize, false);
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	ImGui::Checkbox("Ambient", staticBool);
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	ImGui::Image((void*)(intptr_t)textureManager->Get(textureManager->GetTextureIndex(currentAmbient, TEXTURETYPE::Ambient), TEXTURETYPE::Ambient)->GetID(), materialImageSize);
	ImGui::PushItemWidth(materialImageSize.x);
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	if (ImGui::BeginCombo("##AmbientSelect", currentAmbient))
	{
		for (int n = 0; n < ambientList.size(); n++)
		{
			bool is_selected = (currentNormal == ambientList[n].c_str());
			if (ImGui::Selectable(ambientList[n].c_str(), is_selected))
				currentAmbient = ambientList[n].c_str();
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	ImGui::PushItemWidth(materialImageSize.x);
	ImGui::SliderFloat("##AmbientStrength", &ambientStrength, 0, 1);
	ImGui::EndChild();
#pragma endregion

#pragma region Rough
	// Rough
	ImGui::SameLine();
	ImGui::BeginChild("Rough", childSize, false);
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	ImGui::Checkbox("Rough", staticBool);
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	ImGui::Image((void*)(intptr_t)textureManager->Get(textureManager->GetTextureIndex(currentRough, TEXTURETYPE::Rough), TEXTURETYPE::Rough)->GetID(), materialImageSize);
	ImGui::PushItemWidth(materialImageSize.x);
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	if (ImGui::BeginCombo("##RoughSelect", currentRough))
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
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	ImGui::PushItemWidth(materialImageSize.x);
	ImGui::SliderFloat("##RoughStrength", &roughStrength, 0, 1);
	ImGui::EndChild();
#pragma endregion

#pragma region Displacement
	// Displacment
	ImGui::SameLine();
	ImGui::BeginChild("Displacement", childSize, false);
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	ImGui::Checkbox("Displacement", staticBool);
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	ImGui::Image((void*)(intptr_t)textureManager->Get(textureManager->GetTextureIndex(currentDisplacement, TEXTURETYPE::Displacement), TEXTURETYPE::Displacement)->GetID(), materialImageSize);
	ImGui::PushItemWidth(materialImageSize.x);
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	if (ImGui::BeginCombo("##DisplacementSelect", currentDisplacement))
	{
		for (int n = 0; n < displacementList.size(); n++)
		{
			bool is_selected = (currentDisplacement == displacementList[n].c_str());
			if (ImGui::Selectable(displacementList[n].c_str(), is_selected))
				currentDisplacement = displacementList[n].c_str();
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	ImGui::NewLine();
	ImGui::SameLine(childcenter);
	ImGui::PushItemWidth(materialImageSize.x);
	ImGui::SliderFloat("##DisplacementStrength", &displacementStrength, 0, 1);
	ImGui::EndChild();
#pragma endregion

	if (currentValues[0] != std::string(currentAlbedo) ||
		currentValues[1] != std::string(currentSpecular) ||
		currentValues[2] != std::string(currentNormal) ||
		currentValues[3] != std::string(currentAmbient) ||
		currentValues[4] != std::string(currentRough) ||
		currentValues[5] != std::string(currentDisplacement) ||
		currentStrengthValues[0] != diffuseStrength ||
		currentStrengthValues[1] != specularStrength ||
		currentStrengthValues[2] != normalStrength ||
		currentStrengthValues[3] != ambientStrength ||
		currentStrengthValues[4] != roughStrength ||
		currentStrengthValues[5] != displacementStrength
		)
	matManager->Get(currentEditorMaterial)->SetAll(
		textureManager->Get(currentAlbedo, TEXTURETYPE::Albedo) != nullptr ? textureManager->Get(currentAlbedo, TEXTURETYPE::Albedo) : nullptr,
		textureManager->Get(currentSpecular, TEXTURETYPE::Specular) != nullptr ? textureManager->Get(currentSpecular, TEXTURETYPE::Specular) : nullptr,
		textureManager->Get(currentNormal, TEXTURETYPE::Normal) != nullptr ? textureManager->Get(currentNormal, TEXTURETYPE::Normal) : nullptr,
		textureManager->Get(currentAmbient, TEXTURETYPE::Ambient) != nullptr ? textureManager->Get(currentAmbient, TEXTURETYPE::Ambient) : nullptr,
		textureManager->Get(currentRough, TEXTURETYPE::Rough) != nullptr ? textureManager->Get(currentRough, TEXTURETYPE::Rough) : nullptr,
		textureManager->Get(currentDisplacement, TEXTURETYPE::Displacement) != nullptr ? textureManager->Get(currentDisplacement, TEXTURETYPE::Displacement) : nullptr,
		diffuseStrength,
		specularStrength,
		normalStrength,
		ambientStrength,
		roughStrength,
		displacementStrength
	);

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
			if (ImGui::MenuItem("Delete")) 
			{
				if (currentObject != -1)
				{
					objManager->DeleteObject(objManager->Get(currentObject));
					objectList = objManager->GetNameVector();
					currentObject = -1;
				}
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Create Empty")) 
			{
				currentMaterial = materialList[0].c_str();
				currentShaderName = shaderList[0].c_str();
				currentMesh = meshList[0].c_str();

				if (currentObject != -1)
					objManager->Create(objManager->Get(currentObject),"New Object");
				else
					objManager->Create(nullptr, "New Object");


				objectList = objManager->GetNameVector();
				currentObject = objManager->GetObjectSize() - 1;
			}

			if (ImGui::BeginMenu("Create Object"))
			{
				if (ImGui::MenuItem("Cube"))
				{
					currentMaterial = "defaultMaterial";
					currentShaderName = "pbrShader";
					currentMesh = "Cube";

					if (currentObject != -1)
						objManager->Create(objManager->Get(currentObject), "New Cube");
					else
						objManager->Create(nullptr, "New Cube");


					objectList = objManager->GetNameVector();
					currentObject = objManager->GetObjectSize() - 1;
				}

				if (ImGui::MenuItem("Plane"))
				{
					currentMaterial = "defaultMaterial";
					currentShaderName = "pbrShader";
					currentMesh = "Plane";

					if (currentObject != -1)
						objManager->Create(objManager->Get(currentObject), "New Plane");
					else
						objManager->Create(nullptr, "New Plane");


					objectList = objManager->GetNameVector();
					currentObject = objManager->GetObjectSize() - 1;
				}

				if (ImGui::MenuItem("Cylinder"))
				{
					currentMaterial = "defaultMaterial";
					currentShaderName = "pbrShader";
					currentMesh = "Cylinder";

					if (currentObject != -1)
						objManager->Create(objManager->Get(currentObject), "New Cylinder");
					else
						objManager->Create(nullptr, "New Cylinder");


					objectList = objManager->GetNameVector();
					currentObject = objManager->GetObjectSize() - 1;

				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Create Light"))
			{
				if (ImGui::MenuItem("Directional Light")) {}

				if (ImGui::MenuItem("Point Light"))
				{
					currentMaterial = materialList[0].c_str();
					currentShaderName = shaderList[0].c_str();
					currentMesh = meshList[0].c_str();

					if (currentObject != -1)
						objManager->CreatePointLight("New Point Light", glm::vec3(0), objManager->Get(currentObject));
					else
						objManager->CreatePointLight("New Point Light", glm::vec3(0), nullptr);

					objectList = objManager->GetNameVector();
					currentObject = objManager->GetObjectSize() - 1;

				}
				ImGui::EndMenu();
			}

			ImGui::EndPopup();
		}

		if (ImGui::IsMouseReleased(0) && ImGui::IsMouseHoveringWindow())
			currentObject = -1;

		for (int i = 0; i < objectList.size(); i++)
		{
			if (objManager->Get(i)->GetChildCount() > 0)
				ShowChildObject(objectList[i].c_str(), i);
			else if (objManager->Get(i)->GetParent() == nullptr)
			{
				ImGui::AlignTextToFramePadding();
				if (ImGui::Selectable(objManager->GetObjectName(i).c_str(), currentObject == i))
					currentObject = i;
			}
		}
		ImGui::EndChild();
		ImGui::SameLine();

		// right
		ImGui::BeginGroup();
		ImGui::BeginChild("Object view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));

		if (currentObject == -1)
		{
			ImGui::TextColored(ImVec4(1, 0, 0, 1), "No Item Selected");
			ImGui::EndChild();
			ImGui::EndGroup();
			ImGui::End();
			return;
		}

		ImGui::Text(std::string(objectList[currentObject]).c_str());
		ImGui::Separator();

		GameObject* currentOBJ = objManager->Get(currentObject);

		//Setting vars
		objNameCharP = &objectList[currentObject][0];

		glm::vec3 tempPos = currentOBJ->GetPos();
		pos[0] = tempPos.x;
		pos[1] = tempPos.y;
		pos[2] = tempPos.z;
		
		glm::vec3 tempScale = currentOBJ->GetScale();
		scale[0] = tempScale.x;
		scale[1] = tempScale.y;
		scale[2] = tempScale.z;


		if (currentOBJ->GetMaterial() != nullptr)
			currentMaterial =  materialList[matManager->GetIndex(currentOBJ->GetMaterial())].c_str();

		if (currentOBJ->GetMesh() != nullptr)
			currentMesh = meshList[meshManager->GetIndex(currentOBJ->GetMesh())].c_str();
		
		if (currentOBJ->GetShader() != nullptr)
			currentShaderName = shaderList[shaderManager->GetIndex(currentOBJ->GetShader())].c_str();



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

		bool isLight = currentOBJ->GetIsLight();

		if (isLight)
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "This Object is a Light");
		else
			ImGui::TextColored(ImVec4(0.5f, 0.25f, 0, 1), "This Object is not a Light");

		//Transform
		ImGui::Text("Transform");
		ImGui::Separator();
		ImGui::InputFloat3("Position", pos, 4);
		ImGui::InputFloat3("Rotation", rot, 4);
		ImGui::InputFloat3("Scale", scale, 4);

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

		if (isLight)
		{
			ImGui::Separator();
			ImGui::TextColored(ImVec4(1,1,0,1), "Light Properties");
			PointLight* currentLight = (PointLight*)currentOBJ;
			glm::vec3 difColorvec = currentLight->GetAlbedo();
			float difColor[3] = { difColorvec.x,difColorvec.y,difColorvec.z };
			ImGui::InputFloat3("AlbedoColor",difColor);
			currentLight->SetAlbedo(glm::vec3(difColor[0], difColor[1], difColor[2]));
		}

			objManager->SetVars(
				currentObject,
				objNameCharP,
				staticBool,
				glm::vec3(pos[0], pos[1], pos[2]),
				glm::vec3(rot[0], rot[1], rot[2]),
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
		GameObject* currentOBJ = objManager->Get(uid);
		if (currentOBJ->GetChildCount() <= 0)
			return;
		
		std::string name = "This (" + objectList[uid] + ")";

		if (ImGui::Selectable(name.c_str(), currentObject == objManager->FindIndex(currentOBJ)))
			currentObject = objManager->FindIndex(currentOBJ);

		for (int i = 0; i < currentOBJ->GetChildCount(); i++)
		{
			GameObject* currentChild = currentOBJ->GetChild(i);

			if (currentOBJ->GetChildren()[i]->GetChildCount() > 0)
			{
				ImGui::PushID(i);
				ShowChildObject(currentChild->GetName().c_str(), objManager->FindIndex(currentChild));
				ImGui::PopID();
			}
			else
			{
				ImGui::PushID(i);
				if (ImGui::Selectable(currentChild->GetName().c_str(), currentObject == objManager->FindIndex(currentChild)))
					currentObject = objManager->FindIndex(currentChild);
				ImGui::PopID();
			}
		}
		ImGui::TreePop();
	}
	ImGui::PopID();
}