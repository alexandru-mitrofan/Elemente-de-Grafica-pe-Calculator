#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include "lab_m1/Tema2/transform3D.h"
#include "lab_m1/Tema2/object3D.h"

#include "utils/glm_utils.h"
#include "utils/math_utils.h"


using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    polygonMode = GL_FILL;
    Mesh* mesh = new Mesh("box");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    meshes[mesh->GetMeshID()] = mesh;

    camera = new implemented::Camera1();
    //camera->Set(glm::vec3(8.4,0.30,-0.45),glm::vec3(8.4,0.05,0),glm::vec3(0,1,0));


    std::vector<glm::vec3> centernpc;
    flagdir = 1;
    carOrientation = glm::vec3(0, 0, 1);
    // Initialize tx, ty and tz (the translation steps)
    translateX = 0;
    translateY = 0;
    translateZ = 0;

    // Initialize sx, sy and sz (the scale factors)
    scaleX = 1;
    scaleY = 1;
    scaleZ = 1;

    // Initialize angular steps
    angularStepOX = 0;
    angularStepOY = 0;
    angularStepOZ = 0;

    std::vector<glm::vec3> punctemij = {
		glm::vec3(- 7, 0.05f, 1), 
		glm::vec3(-5.45, 0.05f, 2.53),
		glm::vec3(- 3.51, 0.05f, 2.47), 
		glm::vec3(-2.05, 0.05f, 1.61), 
		glm::vec3(0.75, 0.05f, 1.71), 
		glm::vec3(2.41, 0.05f, 2.77), 
		glm::vec3(3.91, 0.05f, 2.69), 
		glm::vec3(4.91, 0.05f, 1.39), 
		glm::vec3(4.53, 0.05f, -1),
		glm::vec3(3.23, 0.05f, -1.93), 
		glm::vec3(1.39, 0.05f, -1.79), 
		glm::vec3(- 1, 0.05f, -1), 
		glm::vec3(-3.09, 0.05f, -1.85), 
		glm::vec3(- 5.27, 0.05f, -1.63), 
		glm::vec3(- 7, 0.05f, -1)
	};
    std::vector<glm::vec3> punctesus;
    std::vector<glm::vec3> punctejos;
    for(int i=0 ;i < 14; i++){
		punctesus .push_back( object3D::punctsus(punctemij[i],punctemij[i+1],1));
        copacisus .push_back( object3D::punctsus(punctemij[i],punctemij[i+1],1.45));
        npcsus .push_back( object3D::punctsus(punctemij[i],punctemij[i+1],0.5));



		punctejos .push_back( object3D::punctjos(punctemij[i],punctemij[i+1],1));
        copacijos .push_back( object3D::punctjos(punctemij[i],punctemij[i+1],1.45));
        npcjos .push_back( object3D::punctjos(punctemij[i],punctemij[i+1],0.5));

	}
    punctesus .push_back( object3D::punctsus(punctemij[14],punctemij[0],1));
    copacisus .push_back( object3D::punctsus(punctemij[14],punctemij[0],1.45));
    npcsus .push_back( object3D::punctsus(punctemij[14],punctemij[0],0.5));

	punctejos .push_back( object3D::punctjos(punctemij[14],punctemij[0],1));
    copacijos .push_back( object3D::punctjos(punctemij[14],punctemij[0],1.45));
    npcjos .push_back( object3D::punctjos(punctemij[14],punctemij[0],0.5));

	for(int i = 0; i < 15; i++){
		combinate.push_back(punctesus[i]);
		combinate.push_back(punctejos[i]);
	}
	combinate.push_back(punctesus[0]);
	combinate.push_back(punctejos[0]);

//pt npccccccmijloc
    traseunpc1 = object3D::impartetraseupuncte(punctemij,densitatepct,nrpct);
    unghinpc1 = object3D::unghiurinpc(punctemij,nrpct);


//ptnpcsus
    traseunpc2 = object3D::impartetraseupuncte(npcsus,densitatepct,nrpct);
    unghinpc2 = object3D::unghiurinpc(npcsus,nrpct);

//ptnpcjos
    traseunpc3 = object3D::impartetraseupuncte(npcjos,densitatepct,nrpct);
    unghinpc3 = object3D::unghiurinpc(npcjos,nrpct);



    glm::vec3 spcar = glm::vec3(0, 0.25, 0);
    Mesh* mycar = object3D::CreateRectangle("mycar", spcar , 0.15, 0.15, 0.3, glm::vec3(0, 0, 1));
    meshes["mycar"] = mycar;

    spcar = glm::vec3(0, 0.15, 0);
    Mesh* npc1 = object3D::CreateRectangle("npc1", spcar , 0.20, 0.20, 0.4, glm::vec3(0, 1, 0));
    meshes["npc1"] = npc1;

    glm::vec3 sptree = glm::vec3(0, 0.25, 0);
    Mesh* tree = object3D::CreatetrTree("tree", sptree , 0.5, 0.15, 0.15, glm::vec3(0.36, 0.25 ,0.20),glm::vec3( 0.56,0.73,0.56));
    meshes["tree"] = tree;

    glm::vec3 corner = glm::vec3(-25, 0, -25);
    Mesh* map = object3D::CreateMap("map", corner , 500 , glm::vec3(0.5f, 1.0f ,0.5f));
    meshes["map"] = map;
    
    
    corner = glm::vec3(-25, 0, -25);
    Mesh* lap = object3D::CreateLap2("lap", punctesus, punctejos, densitatepct,nrpct,glm::vec3(0.1f, 0.1f, 0.1f));
    meshes["lap"] = lap;

    {
        Shader *shader = new Shader("TemaShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }







    // Sets the resolution of the small viewport
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);
}

void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::RenderScene() {
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(playercar.x, playercar.y,playercar.z);
    modelMatrix *= transform3D::RotateOY(carAngle);
    RenderMesh1(meshes["mycar"], shaders["VertexNormal"], modelMatrix);

    //npc1
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(traseunpc1[npc1cont].x, 0,traseunpc1[npc1cont].z);
    modelMatrix *= transform3D::RotateOY(unghinpc1[npc1cont / densitatepct]);
    RenderMesh1(meshes["npc1"], shaders["VertexColor"], modelMatrix);

    //npc2
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(traseunpc2[npc2cont].x, 0,traseunpc2[npc2cont].z);
    modelMatrix *= transform3D::RotateOY(unghinpc2[npc2cont / densitatepct]);
    RenderMesh1(meshes["npc1"], shaders["VertexColor"], modelMatrix);


    //npc3
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(traseunpc3[npc3cont].x, 0,traseunpc3[npc3cont].z);
    modelMatrix *= transform3D::RotateOY(unghinpc3[npc3cont / densitatepct]);
    RenderMesh1(meshes["npc1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    RenderMesh1(meshes["map"], shaders["VertexColor"], modelMatrix);


    for(int i = 0;i < nrpct; i++){
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(copacisus[i].x, 0,copacisus[i].z);

        RenderMesh1(meshes["tree"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(copacijos[i].x, 0,copacijos[i].z);

        RenderMesh1(meshes["tree"], shaders["VertexColor"], modelMatrix);

    }


    modelMatrix = glm::mat4(1);
    RenderMesh1(meshes["lap"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0, 0.05, 0);
    RenderMesh1(meshes["line"], shaders["VertexColor"], modelMatrix);


}
void Tema2::RenderSimpleScene() {
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(playercar.x, playercar.y,playercar.z);
    modelMatrix *= transform3D::RotateOY(carAngle);
    RenderSimpleMesh(meshes["mycar"], shaders["TemaShader"], modelMatrix);

    //npc1
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(traseunpc1[npc1cont].x, 0,traseunpc1[npc1cont].z);
    modelMatrix *= transform3D::RotateOY(unghinpc1[npc1cont / densitatepct]);
    RenderSimpleMesh(meshes["npc1"], shaders["TemaShader"], modelMatrix);
    npc1cont--;
    if (npc1cont < 0){
        npc1cont = densitatepct * nrpct - 1;
    }


    //npc2
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(traseunpc2[npc2cont].x, 0,traseunpc2[npc2cont].z);
    modelMatrix *= transform3D::RotateOY(unghinpc2[npc2cont / densitatepct]);
    RenderSimpleMesh(meshes["npc1"], shaders["TemaShader"], modelMatrix);
    npc2cont--;
    if (npc2cont < 0){
        npc2cont = densitatepct * nrpct - 1;
    }

    //npc3
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(traseunpc3[npc3cont].x, 0,traseunpc3[npc3cont].z);
    modelMatrix *= transform3D::RotateOY(unghinpc3[npc3cont / densitatepct]);
    RenderSimpleMesh(meshes["npc1"], shaders["TemaShader"], modelMatrix);

    npc3cont--;
    if (npc3cont < 0){
        npc3cont = densitatepct * nrpct - 1;
    }



    modelMatrix = glm::mat4(1);
    RenderSimpleMesh(meshes["map"], shaders["TemaShader"], modelMatrix);


    for(int i = 0;i < nrpct; i++){
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(copacisus[i].x, 0,copacisus[i].z);

        RenderSimpleMesh(meshes["tree"], shaders["TemaShader"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(copacijos[i].x, 0,copacijos[i].z);

        RenderSimpleMesh(meshes["tree"], shaders["TemaShader"], modelMatrix);

    }


    modelMatrix = glm::mat4(1);
    RenderSimpleMesh(meshes["lap"], shaders["TemaShader"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0, 0.05, 0);
    RenderSimpleMesh(meshes["line"], shaders["TemaShader"], modelMatrix);

}



void Tema2::Update(float deltaTimeSeconds)
{
    projectionMatrix1 = glm::perspective(RADIANS(85), window->props.aspectRatio, 0.01f, 400.0f);
    camera->Set(playercar + glm::vec3(-0.5 * sin(carAngle),0.5,-0.5 * cos(carAngle)), playercar, glm::vec3(0, 1, 0));

    RenderSimpleScene();

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);
    projectionMatrix = glm::ortho(-4.f, 4.f, -4.f, 4.f, 0.01f, 200.0f);
    camera->Set(playercar + glm::vec3(0,1,0), playercar, glm::vec3(0, 0, 1));

    RenderScene();
}

void Tema2::FrameEnd()
{

}

void Tema2::RenderMesh1(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}
void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // TODO(student): Get shader location for uniform mat4 "Model"
    

    int location = glGetUniformLocation(shader->program, "pozcar");
    glUniform3fv(location, 1, glm::value_ptr(playercar));


    location = glGetUniformLocation(shader->program, "factors");
    glUniform1f(location, fscalare);

    // TODO(student): Set shader uniform "Model" to modelMatrix
    location = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(location, 1, 0, glm::value_ptr(modelMatrix));

    // TODO(student): Get shader location for uniform mat4 "View"
    location = glGetUniformLocation(shader->program, "View");

    // TODO(student): Set shader uniform "View" to viewMatrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // TODO(student): Get shader location for uniform mat4 "Projection"
    location = glGetUniformLocation(shader->program, "Projection");

    // TODO(student): Set shader uniform "Projection" to projectionMatrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
    
    
    shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix1));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}
/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{




    //if coliziune npc
    if(object3D::bummasina(playercar,traseunpc1[npc1cont]) == 0 &&
    object3D::bummasina(playercar,traseunpc2[npc2cont]) == 0 &&
    object3D::bummasina(playercar,traseunpc3[npc3cont]) == 0)
        {
            flagdir = 1;
        if (window->KeyHold(GLFW_KEY_W)){
            helpercoliz.x = (carOrientation.x) * deltaTime + playercar.x;
            helpercoliz.z = (carOrientation.z) * deltaTime + playercar.z;
            //vercoliziune cu marginea
            if(object3D::vercoliziune(combinate,helpercoliz) == 1){
                playercar.x = helpercoliz.x;
                playercar.z = helpercoliz.z;
            }
        }
        if (window->KeyHold(GLFW_KEY_S)){
        
            helpercoliz.x = (-1) * (carOrientation.x) * deltaTime + playercar.x;
            helpercoliz.z = (-1) * (carOrientation.z) * deltaTime + playercar.z;
            //vercoliziune cu marginea
            if(object3D::vercoliziune(combinate,helpercoliz) == 1){
                playercar.x = helpercoliz.x;
                playercar.z = helpercoliz.z;
                flagdir = -1;
            }
        }
        if (window->KeyHold(GLFW_KEY_A)){

            carAngle = carAngle + 0.8 * deltaTime * flagdir;
            carOrientation = glm::normalize(glm::vec3(sin(carAngle) / 10,0,cos(carAngle) / 10));
        }
        if (window->KeyHold(GLFW_KEY_D)){
            carAngle = carAngle -  0.8 * deltaTime * flagdir;
            carOrientation = glm::normalize(glm::vec3(sin(carAngle) / 10,0, cos(carAngle) / 10));
        }
    }

    // TODO(student): Add transformation logic

}


void Tema2::OnKeyPress(int key, int mods)
{
    
    // TODO(student): Add viewport movement and scaling logic
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
