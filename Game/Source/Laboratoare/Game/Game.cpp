#include "Game.h"

#include <vector>
#include <iostream>
#include <math.h>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

float height = 0;
int keypressed = 0;
float translateXbird = 50;
float translateYbird = 250;
int resolutiony;
int resolutionx;
int score = -2;
int gameover = 0;
float rotangle = 0;
int counter = 0; 
int scaleX2 = 1;
int scaleY2 = (float)rand() / (float)(RAND_MAX / 4);
int feather = 0;
float featherangle = 0;
Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;
	float squareSide2 = 50;
	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;

	// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 0;
	translateX2 = 0;
	translateY2 = 0;
	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = (float)rand() / (float)(RAND_MAX / 4);

	// initialize angularStep
	angularStep = 10;

	//CORP/COADA
	Mesh* circle1 = Object2D::CreateCircle("circle1", glm::vec3(1, 1, 0), true);
	AddMeshToList(circle1);
	//CERC PT NORI
	Mesh* circle2 = Object2D::CreateCircle("circle2", glm::vec3(1, 1, 1), true);
	AddMeshToList(circle2);
	//ARIPA/CAP
	Mesh* circle4 = Object2D::CreateCircle("circle4", glm::vec3(1, 0.85f, 0), true);
	AddMeshToList(circle4);
	//OCHI
	Mesh* circle5 = Object2D::CreateCircle("circle5", glm::vec3(0, 0, 0), true);
	AddMeshToList(circle5);
	//TUBURI
	Mesh* square4 = Object2D::CreateSquare("square4", corner, squareSide, glm::vec3(0.19f, 0.80f, 0.19f), true);
	AddMeshToList(square4);
	//PAMANT
	Mesh* square5 = Object2D::CreateSquare("square5", corner, squareSide, glm::vec3(0.62f, 0.35f, 0.176f), true);
	AddMeshToList(square5);
	//CONTUR TUBURI
	Mesh* square6 = Object2D::CreateSquare("square6", corner, squareSide, glm::vec3(0, 0, 0));
	AddMeshToList(square6);
	//CIOC
	Mesh* triangle1 = Object2D::CreateTriangle("triangle1", corner, squareSide, glm::vec3(1, 0.46f, 0), true);
	AddMeshToList(triangle1);
}

void Game::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.53f, 0.81f, 0.94f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
	resolutionx = resolution.x;
	resolutiony = resolution.y;
}

void Game::Update(float deltaTimeSeconds)
{

	//ARIPA PASARII
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateXbird, translateYbird);
					//Rotatia aripii pasarii
	if (feather == 0 && featherangle < 0.8f) {
		modelMatrix *= Transform2D::Rotate(featherangle);
		featherangle += 0.1f;
		if (featherangle >= 0.8f)
			feather = 1;
	}
	else if (feather == 1 && featherangle > -0.8f) {
		modelMatrix *= Transform2D::Rotate(featherangle);
		featherangle -= 0.1f;
		if (featherangle <= -0.8f)
			feather = 0;
	}				//Translatie pt rotatia aripii
	modelMatrix *= Transform2D::Translate(-5,0);
					//Functii rotatie pt cadere/ridicare
	if (keypressed == 1) {
		modelMatrix *= Transform2D::Rotate(rotangle);
		if (rotangle < M_PI / 4) {
			rotangle += 0.01;
		}
	}
	else if (keypressed == 0) {
		modelMatrix *= Transform2D::Rotate(rotangle);
		if (rotangle > -(M_PI / 4)) {
			rotangle -= 0.02;
		}
	}
	modelMatrix *= Transform2D::Scale(12, 5);
	RenderMesh2D(meshes["circle4"], shaders["VertexColor"], modelMatrix);

	//COADA PASARII 
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateXbird, translateYbird);
				//Functii rotatie pt cadere/ridicare
	if (keypressed == 1) {
		modelMatrix *= Transform2D::Rotate(rotangle);
		if (rotangle < M_PI / 4) {
			rotangle += 0.05;
		}
	}
	else if (keypressed == 0) {
		modelMatrix *= Transform2D::Rotate(rotangle);
		if (rotangle > -(M_PI / 4)) {
			rotangle -= 0.02;
		}
	}
	modelMatrix *= Transform2D::Translate(-17,-17);
	modelMatrix *= Transform2D::Scale(5, 5);
	RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix);

	//CIOCUL PASARII 
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateXbird, translateYbird);
	modelMatrix *= Transform2D::Scale(0.1f, 0.1f);
				//Functii rotatie pt cadere/ridicare
	if (keypressed == 1) {
		modelMatrix *= Transform2D::Rotate(rotangle);
		if (rotangle < M_PI / 4) {
			rotangle += 0.01;
		}
	}
	else if (keypressed == 0) {
		modelMatrix *= Transform2D::Rotate(rotangle);
		if (rotangle > -(M_PI / 4)) {
			rotangle -= 0.02;
		}
	}
	modelMatrix *= Transform2D::Translate(325, 5);
	modelMatrix *= Transform2D::Translate(-50, -33);
	RenderMesh2D(meshes["triangle1"], shaders["VertexColor"], modelMatrix);
	
	//OCHIUL PASARII 
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateXbird, translateYbird);
				//Functii rotatie pt cadere/ridicare
	if (keypressed == 1) {
		modelMatrix *= Transform2D::Rotate(rotangle);
		if (rotangle < M_PI / 4) {
			rotangle += 0.01;
		}
	}
	else if (keypressed == 0) {
		modelMatrix *= Transform2D::Rotate(rotangle);
		if (rotangle > -(M_PI / 4)) {
			rotangle -= 0.02;
		}
	}
	modelMatrix *= Transform2D::Translate(20, 10);
	modelMatrix *= Transform2D::Scale(3, 3);
	RenderMesh2D(meshes["circle5"], shaders["VertexColor"], modelMatrix);
	//CAPUL PASARII
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateXbird, translateYbird);
				//Functii rotatie pt cadere/ridicare
	if (keypressed == 1) {
		modelMatrix *= Transform2D::Rotate(rotangle);
		if (rotangle < M_PI /4 ) {
			rotangle += 0.01;
		}
	}
	else if (keypressed == 0) {
		modelMatrix *= Transform2D::Rotate(rotangle);
		if (rotangle > -(M_PI / 4)) {
			rotangle -= 0.02;
		}
	}
	modelMatrix *= Transform2D::Translate(20, 10);
	modelMatrix *= Transform2D::Scale(13, 13);
	RenderMesh2D(meshes["circle4"], shaders["VertexColor"], modelMatrix);

	//CORPUL PASARII
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateXbird, translateYbird);
				//Functii rotatie pt cadere/ridicare
	if (keypressed == 1) {
		modelMatrix *= Transform2D::Rotate(rotangle);
		if (rotangle < M_PI / 4) {
			rotangle += 0.05;
		}
	}
	else if (keypressed == 0) {
		modelMatrix *= Transform2D::Rotate(rotangle);
		if (rotangle > -(M_PI / 4)) {
			rotangle -= 0.02;
		}
	}
	modelMatrix *= Transform2D::Scale(20, 20);
	RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix);

	//TUBURILE 1
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Scale(scaleX, scaleY);
	modelMatrix *= Transform2D::Translate(translateX, translateY);
	RenderMesh2D(meshes["square6"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Scale(scaleX, scaleY);
	modelMatrix *= Transform2D::Translate(translateX, translateY);
	RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateX, 0);
	modelMatrix *= Transform2D::Translate(100, resolutiony);
	modelMatrix *= Transform2D::Rotate(M_PI);
	modelMatrix *= Transform2D::Scale(scaleX, resolutiony / 100 - 2 - scaleY);
	RenderMesh2D(meshes["square6"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateX, 0);
	modelMatrix *= Transform2D::Translate(100, resolutiony);
	modelMatrix *= Transform2D::Rotate(M_PI);
	modelMatrix *= Transform2D::Scale(scaleX, resolutiony / 100 - 2 - scaleY);
	RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);


	//TUBURILE 2
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Scale(scaleX2, scaleY2);
	modelMatrix *= Transform2D::Translate(translateX2, translateY2);
	RenderMesh2D(meshes["square6"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Scale(scaleX, scaleY2);
	modelMatrix *= Transform2D::Translate(translateX2, translateY2);
	RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateX2, 0);
	modelMatrix *= Transform2D::Translate(100, resolutiony);
	modelMatrix *= Transform2D::Rotate(M_PI);
	modelMatrix *= Transform2D::Scale(scaleX2, resolutiony / 100 - 2 - scaleY2);
	RenderMesh2D(meshes["square6"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateX2, 0);
	modelMatrix *= Transform2D::Translate(100, resolutiony);
	modelMatrix *= Transform2D::Rotate(M_PI);
	modelMatrix *= Transform2D::Scale(scaleX2, resolutiony / 100 - 2 - scaleY2);
	RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);
	

	//LINIA DE PAMANT
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Scale(resolutionx / 100 + 1, 0.25);
	RenderMesh2D(meshes["square5"], shaders["VertexColor"], modelMatrix);

	//NORII

	//NOR1
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolutionx/4, resolutiony - 100);
	modelMatrix *= Transform2D::Scale(40, 40);
	RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolutionx / 4 + 50, resolutiony - 100);
	modelMatrix *= Transform2D::Scale(25, 25);
	RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolutionx / 4 -50, resolutiony - 100);
	modelMatrix *= Transform2D::Scale(25, 25);
	RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);

	//NOR2
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolutionx / 2, resolutiony - 200);
	modelMatrix *= Transform2D::Scale(40, 40);
	RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolutionx / 2 + 50, resolutiony - 200);
	modelMatrix *= Transform2D::Scale(25, 25);
	RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolutionx / 2 - 50, resolutiony - 200);
	modelMatrix *= Transform2D::Scale(25, 25);
	RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);

	//SOARELE
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolutionx - 100, resolutiony - 100);
	modelMatrix *= Transform2D::Scale(100, 100);
	RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix);


	if (gameover == 0) {
		//Caderea continua a pasarii
		if (translateYbird > 0) {
			translateYbird -= 200 * deltaTimeSeconds;
		}
		//Functia de marire a dificultatii jocului in functie de scor. Viteza se mareste cand scorul reprezinta un multiplu de 10 pana la 600*time, o viteza aproape imposibil de controlat tinand
		//cont de modul in care sunt construite tuburile
		float time = deltaTimeSeconds;
		if (score < 10) {
			translateX -= 200 * time;
			translateX2 -= 200 * time;
		}
		else if (score >= 10 && score <20) {
			translateX -= 300 * time;
			translateX2 -= 300 * time;
		}
		else if (score >= 20 && score < 30) {
			translateX -= 400 * time;
			translateX2 -= 400 * time;
		}
		else if (score >= 30 && score < 40) {
			translateX -= 500 * time;
			translateX2 -= 500 * time;
		}
		else if (score >= 40 ) {
			translateX -= 600 * time;
			translateX2 -= 600 * time;
		}
	}
	//Daca jocul e pierdut, pasarea cade in jos pana la baza cadrului
	else if (gameover == 1) {
		if (translateYbird > 25) {
			translateYbird -= 600 * deltaTimeSeconds;
		}
	}
	//Functia de resetare a primului set de tuburi si de incrementare a scorului
	if (translateX < -100) {
		translateX = resolutionx;
		scaleY = (float)rand() / (float)(RAND_MAX / 4);
		score++;
		if ( score >= 0)
			printf("Your score is %d\n", score);
	}
	//Functia de resetare a perechii 2 de tuburi la inceputul jocului
	if (translateX2 < -(100+resolutionx/2) && counter == 0) {
		translateX2 = resolutionx;
		scaleY2 = (float)rand() / (float)(RAND_MAX / 4);
		score++;
		if (score >= 0)
			printf("Your score is %d\n", score);
		counter++;
	}
	//Dupa prima serie de tuburi, totul intra in normal si perechea nr 2 de tuburi se reseteaza la fel ca prima
	else if (translateX2 < -100 && counter == 1) {
		translateX2 = resolutionx;
		scaleY2 = (float)rand() / (float)(RAND_MAX / 4);
		score++;
		if (score >=0)
			printf("Your score is %d\n", score);
	}
	  //FUNCTII PT VERIFICAREA COLIZIUNILOR (inspirate din primul link dat in enuntul temei, cate una pt fiecare tub prezent pe ecran
	if (gameover == 0) {
		if  (
			((translateXbird < translateX + 100) &&
			(translateXbird + 20 > translateX) &&
			(translateYbird < translateY + 100 * scaleY) &&
			(translateYbird + 20 > translateY)) 
			||
			((translateXbird < translateX + 100) &&
			(translateXbird + 20 > translateX) &&
			(translateYbird < translateY + 200 + 100 * scaleY + (resolutiony - 200 - 100 * scaleY)) &&
			(translateYbird + 20 > translateY + 200 + 100 * scaleY)) 
			||
			((translateXbird < translateX2 + 100) &&
			(translateXbird + 25 > translateX2) &&
			(translateYbird < translateY2 + 100 * scaleY2) &&
			(translateYbird + 25 > translateY2) ) 
			||
			((translateXbird < translateX2 + 100) &&
			(translateXbird + 25 > translateX2) &&
			(translateYbird < translateY2 + 200 + 100 * scaleY2 + (resolutiony - 200 - 100 * scaleY2)) &&
			(translateYbird + 25 > translateY2 + 200 + 100 * scaleY2))
			)
		{
			printf("GAME OVER ! YOUR FINAL SCORE IS %d!\n", score);
			printf("Click F to restart the game!\n");
			gameover = 1;
		}
	}


}

void Game::FrameEnd()
{

}

void Game::OnInputUpdate(float deltaTime, int mods)
{
	//Spatiul dintre tuburi este 200. La apasarea tastei SPACE, voi ridica pasarea cu 125, verificand astfel ca pasarea are loc sa treaca printre tuburi
	if (keypressed == 1) {
		if (translateYbird < resolutiony - 75) {
			height += 125 * deltaTime * deltaTime + 20 * deltaTime + 12;
			translateYbird += 125 * deltaTime * deltaTime + 20 * deltaTime + 12;
			if (height > 125) {
				keypressed = 0;
				height = 0;
			}
		}
	}

}

void Game::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE) {
		keypressed = 1;
	}
	//Daca este apasata tasta F si jocul este in stadiul GAME OVER, se reseteaza mapa
	else if (key == GLFW_KEY_F && gameover == 1) {
		gameover = 0;
		score = -2;
		translateX = -100;
		translateX2 = -100;
		translateXbird = 200;
		translateYbird = 200;
		rotangle = 0;
		counter = 0;
	}
}

void Game::OnKeyRelease(int key, int mods)
{
	//keypressed = 0;
}

void Game::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Game::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Game::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Game::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Game::OnWindowResize(int width, int height)
{
}
