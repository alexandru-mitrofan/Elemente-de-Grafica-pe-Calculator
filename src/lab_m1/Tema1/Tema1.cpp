#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"
#include <cmath>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    y1=1;
    x1=1;
    y3=0.0f;
    x3=0.0f;
    nlives=3;
    nbullets=3;
    onMouse=0;
    secBirdOnScreen = 0;
    timp = 0;
    acceleratie = 1;
    nivel = 1;
    semnaripa=1;

    points=0;
    flagx=(rand()%2)*2-1;

    flagy=1;
    flagnivel=1;
    //auto tr = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);;
    
    tr = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);
    tr->Load(window->props.selfDir + "/assets/fonts/Hack-Bold.ttf", 128);


    //unghil de inceput de la axa oy al ratei atan(vitezax/vitezay)*180/pi=grade
    vitezax=rand()%60+30;
    vitezay=rand()%60+30;
    //pnctul de inceput al ratei
    incx=rand()%1000+500;
    vitezatotala=100 / (sqrt(vitezax * vitezax + vitezay * vitezay)) * acceleratie;

    incy=300;
    glm::vec3 corner = glm::vec3(0, 0, 0);

    glm::vec3 A = glm::vec3(0, 0, 0);
    glm::vec3 B = glm::vec3(100, 300, 0);
    glm::vec3 C = glm::vec3(200, 0, 0);

    glm::vec3 A1 = glm::vec3(100, 200, 0);
    glm::vec3 B1 = glm::vec3(0, 200, 0);
    glm::vec3 C1 = glm::vec3(0, 0, 0);

    glm::vec3 A2 = glm::vec3(100, 200, 0);
    glm::vec3 B2 = glm::vec3(200, 0, 0);
    glm::vec3 C2 = glm::vec3(200, 200, 0);
    float squareSide = 100;

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;

    Mesh* cap = object2D::CreateHead("cap", B,70,70, glm::vec3(1, 0, 0));
    AddMeshToList(cap);
    Mesh* vieti = object2D::CreateHead("vieti", corner,20,20, glm::vec3(1, 0, 0));
    AddMeshToList(vieti);
    Mesh* gloante = object2D::CreateS("gloante", corner, 40, glm::vec3(0, 1, 0));
    AddMeshToList(gloante);

    Mesh* corp = object2D::CreateTriangle("corp", A, B, C, glm::vec3(1, 0, 0));
    AddMeshToList(corp);
    Mesh* aripa1 = object2D::CreateTriangle("aripa1", A1, B1, C1, glm::vec3(0, 1, 0));
    AddMeshToList(aripa1);
    Mesh* aripa2 = object2D::CreateTriangle("aripa2", A2, B2, C2, glm::vec3(0, 1, 0));
    AddMeshToList(aripa2);

    Mesh* drgol = object2D::CreateRectangle("drgol",corner , 60, 400, glm::vec3(0, 1, 0), 0);
    AddMeshToList(drgol);

    Mesh* drplin = object2D::CreateRectangle("drplin",corner , 60, 20, glm::vec3(0, 1, 0), 1);
    AddMeshToList(drplin);
        
    Mesh* iarba = object2D::CreateRectangle("iarba",corner , 1000, 10000, glm::vec3(0, 1, 0), 1);
    AddMeshToList(iarba);
    
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{

    if(points >= 20){
        
        tr->RenderText("Game Over", 740, 650, 1);
        tr->RenderText("You win!", 800, 800, 1);
        return;
    }
    if(nlives<=0){
        
        tr->RenderText("Game Over", 740, 650, 1);
        tr->RenderText("You lost!", 800, 800, 1);
        return;
    }
    if(points % 5 == 0 && flagnivel == 1 && points!=0){
        tr->RenderText("Ati trect la urmatorl nivel!", 500, 600, 0.7f);
        timp += deltaTimeSeconds;
    }
    if(timp > 3){
        timp = 0;
        flagnivel = 0;
    }
    modelMatrix = glm::mat3(1);

    RenderMesh2D(meshes["iarba"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(2300, 1370);
    RenderMesh2D(meshes["drgol"], shaders["VertexColor"], modelMatrix);
    for(i = 0;i < points; i++){
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(2100+i*20, 1370);
        RenderMesh2D(meshes["drplin"], shaders["VertexColor"], modelMatrix);
    }
    // add them over there!
    for(i = 0; i < nlives; i++){
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(60 + i * 60, 1400);
        RenderMesh2D(meshes["vieti"], shaders["VertexColor"], modelMatrix);
    }
    for(i = 0; i < nbullets; i++){
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(40 + i * 60, 1320);
        RenderMesh2D(meshes["gloante"], shaders["VertexColor"], modelMatrix);
    }
        //corp
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(incx, incy);
        modelMatrix *= transform2D::Translate(x1, y1);
        if(flagy==1)
            modelMatrix *= transform2D::Rotate((-atan(vitezax/vitezay))*(flagx*flagy));
        else
            modelMatrix *= transform2D::Rotate((-atan(vitezax/vitezay))*(flagx*flagy)+3.14159f);
        RenderMesh2D(meshes["corp"], shaders["VertexColor"], modelMatrix);
        // aripa1
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(incx, incy);
        modelMatrix *= transform2D::Translate(x1, y1);
        if(flagy==1)
            modelMatrix *= transform2D::Rotate((-atan(vitezax/vitezay))*(flagx*flagy));
        else
            modelMatrix *= transform2D::Rotate((-atan(vitezax/vitezay))*(flagx*flagy)+3.14159f);
        modelMatrix *= transform2D::Translate(100, 200);
        modelMatrix *= transform2D::Rotate(angularStep);
        modelMatrix *= transform2D::Translate(-100, -200);

        RenderMesh2D(meshes["aripa1"], shaders["VertexColor"], modelMatrix);

        //aripa2
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(incx, incy);
        modelMatrix *= transform2D::Translate(x1, y1);
        if(flagy==1)
            modelMatrix *= transform2D::Rotate((-atan(vitezax/vitezay))*(flagx*flagy));
        else
            modelMatrix *= transform2D::Rotate((-atan(vitezax/vitezay))*(flagx*flagy)+3.14159f);
        modelMatrix *= transform2D::Translate(100, 200);
        modelMatrix *= transform2D::Rotate(-angularStep);
        modelMatrix *= transform2D::Translate(-100, -200);

        RenderMesh2D(meshes["aripa2"], shaders["VertexColor"], modelMatrix);
        //cap....

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(incx, incy);
        modelMatrix *= transform2D::Translate(x1, y1);
        //modelMatrix *= transform2D::Translate(300, 100);
        if(flagy==1)
            modelMatrix *= transform2D::Rotate((-atan(vitezax/vitezay))*(flagx*flagy));
        else
            modelMatrix *= transform2D::Rotate((-atan(vitezax/vitezay))*(flagx*flagy)+3.14159f);

    //printf_l
        RenderMesh2D(meshes["cap"], shaders["VertexColor"], modelMatrix);


     if(onMouse == 0 && secBirdOnScreen <= 15 && nbullets>0){

        x1 += deltaTimeSeconds * flagx * 4 * vitezax*vitezatotala;
        y1 += deltaTimeSeconds * flagy * 4 * vitezay*vitezatotala;

        if(y1+incy>=1170){

           flagy = -1;

        }
        if(y1+incy<300){

            flagy = 1;
        }
        if(x1+incx>=2200){

            flagx = -1;
        }
        if(x1+incx<300){

            flagx = 1;
        }


    }
    //bataie aripi
    angularStep-=deltaTimeSeconds*semnaripa;
    if(angularStep>0)
        semnaripa=1;
    if (angularStep<-0.5f){
        semnaripa=-1;
    }

    secBirdOnScreen += deltaTimeSeconds;
    if(secBirdOnScreen > 15 || nbullets<=0){
        y1 += deltaTimeSeconds  * 4 * vitezay;
        vitezax=0.001f;
        flagx=1;flagy=1;
        if(y1 + incy >= 1500){

           onMouse=0;
           //viteza c random setata
           //mai trebie schimbat si incx si incy
            flagx=(rand()%2)*2-1;
            vitezax=rand()%60+30;
            vitezay=rand()%60+30;
            incx=rand()%1000+500;
            x1=1;y1=1;
            vitezatotala = 100 / (sqrt(vitezax * vitezax + vitezay * vitezay)) * acceleratie;
            secBirdOnScreen = 0;
            nlives--;
            nbullets = 3;
        }
    }else
    if(onMouse == 1 ){

        secBirdOnScreen = 0;
        //onMouse=2;
        y1 -= deltaTimeSeconds  * 4 * vitezay;
        vitezax=0.001f;
        flagx=1;flagy=-1;

        if(y1+incy<-200){

            onMouse=0;

            flagx=(rand()%2)*2-1;
            vitezax=rand()%60+30;
            vitezay=rand()%60+30;
            incx=rand()%1000+500;
            x1=1;y1=1;
            vitezatotala = 100 / (sqrt(vitezax * vitezax + vitezay * vitezay)) * acceleratie;



            nbullets=3;
            points++;
            flagnivel = 1;
            nivel++;
            if(nivel%5==0)
                acceleratie+=0.6f;


        }
    }

}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if(mouseX > (x1 + incx - 200)/2 && mouseX < (x1 + incx + 200 )/2){
        if(720 - mouseY > (y1 + incy - 200)/2 && 720 - mouseY < (y1 + incy +200)/2){
            if(button == 1 ) {
                onMouse = 1;
                //cout << "Hello World!\n x1="<< x1<<"   y1="<< y1<<"\n";
                //cout << "mouseX="<< mouseX<<"   mouseY1="<< mouseY<<"\n";
            }
        }
    }
    if(button == 1){
        nbullets--;
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
