// ShadingSystem.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "thread.h"
#include "GfxRenderer.h"


float sh_red[9] = { 0.0 };
float sh_green[9] = { 0.0 };
float sh_blue[9] = { 0.0 };

GLuint screenWidth = 500;
GLuint screenHeight = 500;

CGfxCamera *pCamera = NULL;
std::vector<CGfxMesh*> pMeshs;
std::vector<CGfxMaterial*> pMaterials;

THREAD_CLUSTER threadCluster;

void LoadMesh(const char *szFileName)
{
	CGfxMesh *pMesh = CGfxRenderer::GetInstance()->LoadMesh(szFileName);
	pMesh->Lock();
	pMeshs.push_back(pMesh);
}

void FreeMeshs(void)
{
	for (GLuint index = 0; index < pMeshs.size(); index++) {
		pMeshs[index]->Unlock(false);
		CGfxRenderer::GetInstance()->FreeMesh(pMeshs[index]);
	}

	pMeshs.clear();
}

void LoadMaterial(const char *szFileName)
{
	CGfxMaterial *pMaterial = CGfxRenderer::GetInstance()->LoadMaterial(szFileName);
	pMaterial->Lock();
	pMaterials.push_back(pMaterial);
}

void FreeMaterials(void)
{
	for (GLuint index = 0; index < pMaterials.size(); index++) {
		pMaterials[index]->Unlock(false);
		CGfxRenderer::GetInstance()->FreeMaterial(pMaterials[index]);
	}

	pMaterials.clear();
}

void LoadSkyBox(void)
{
	LoadMesh("SkyBox.mesh");
	LoadMaterial("SkyBox.material");

	pCamera->SetLookat(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	if (FILE *pFile = fopen("./Mesh/Env.sh", "rb")) {
		fscanf(pFile, "%f %f %f %f %f %f %f %f %f", &sh_red[0], &sh_red[1], &sh_red[2], &sh_red[3], &sh_red[4], &sh_red[5], &sh_red[6], &sh_red[7], &sh_red[8]);
		fscanf(pFile, "%f %f %f %f %f %f %f %f %f", &sh_green[0], &sh_green[1], &sh_green[2], &sh_green[3], &sh_green[4], &sh_green[5], &sh_green[6], &sh_green[7], &sh_green[8]);
		fscanf(pFile, "%f %f %f %f %f %f %f %f %f", &sh_blue[0], &sh_blue[1], &sh_blue[2], &sh_blue[3], &sh_blue[4], &sh_blue[5], &sh_blue[6], &sh_blue[7], &sh_blue[8]);
		fclose(pFile);

		CGfxRenderer::GetInstance()->SetAmbientLightSH(sh_red, sh_green, sh_blue);
	}
}

void LoadCar(void)
{
	LoadMesh("Car.mesh");
	LoadMaterial("Car.material");

	pCamera->SetLookat(0.0f, 2.0f, 4.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void LoadCarIBL(void)
{
	LoadMesh("Car.mesh");
	LoadMaterial("CarIBL.material");

	pCamera->SetLookat(0.0f, 2.0f, 4.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void LoadTank(void)
{
	LoadMesh("TankBody.mesh");
	LoadMaterial("TankBody.material");

	LoadMesh("TankTrack.mesh");
	LoadMaterial("TankTrack.material");

	pCamera->SetLookat(0.0f, 4.5f, 8.0f, 0.0f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void LoadMarcus(void)
{
	LoadMesh("Marcus.mesh");
	LoadMaterial("Marcus.material");

	pCamera->SetLookat(0.0f, 4.0f, 4.0f, 0.0f, 2.5f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void LoadSphere(const char *szMaterialFileName)
{
	glutReshapeWindow(200, 200);

	LoadMesh("Sphere.mesh");
	LoadMaterial(szMaterialFileName);

	pCamera->SetLookat(0.0f, 0.0f, 2.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}


void RenderSkyBox(void)
{
	glm::mat4 scale = glm::scale(glm::mat4(), glm::vec3(5000.0f, 5000.0f, 5000.0f));
	glm::mat4 rotateX = glm::rotate(glm::mat4(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 transform = rotateX * scale;

	for (GLuint index = 0; index < 1; index++) {
		pCamera->AddQueue(pMaterials[index], pMeshs[index], transform);
	}
}

void RenderMesh(void)
{
	static float angle = 45.0f; angle += 0.5f;
	glm::mat4 rotateX = glm::rotate(glm::mat4(), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotateY = glm::rotate(glm::mat4(), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 translate = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 transform = translate * rotateY * rotateX;

	for (GLuint index = 1; index < pMaterials.size(); index++) {
		pCamera->AddQueue(pMaterials[index], pMeshs[index], transform);
	}
}

void* RenderThread(void*)
{
	pCamera->SetScissor(0, 0, screenWidth, screenHeight);
	pCamera->SetViewport(0, 0, screenWidth, screenHeight);
	pCamera->SetPerspective(60.0f, 1.0f, 0.1f, 100.0f);

	pCamera->SetEnableClearColor(true);
	pCamera->SetEnableClearDepth(true);
	pCamera->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	pCamera->SetClearDepth(1.0f);

	pCamera->ClearQueue();
	{
		RenderSkyBox();
		RenderMesh();
	}
	pCamera->CmdDraw();

	return NULL;
}

void display(void)
{
	WaitThreads(&threadCluster);
	{
		CGfxRenderer::GetInstance()->SetDirectLightColor(3.0f, 3.0f, 3.0f);
		CGfxRenderer::GetInstance()->SetDirectLightDirection(-1.0f, -1.0f, -1.0f);
		pCamera->Submit();
	}
	DispatchThreads(&threadCluster);

	glutSwapBuffers();
}

void timer(int value)
{
	display();
	glutTimerFunc(1000 / 60, timer, 0);
}

void resize(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	glutTimerFunc(1000 / 60, timer, 0);
	glewInit();

	CGfxRenderer::Create("./Shader", "./Mesh", "./Mesh", "./Mesh");
	pCamera = new CGfxCamera;

	LoadSkyBox();
//	LoadCar();
	LoadCarIBL();
//	LoadTank();
//	LoadMarcus();
//	LoadSphere("Car.material");
//	LoadSphere("CarIBL.material");
//	LoadSphere("TankBody.material");
	CreateThreads(&threadCluster, RenderThread, NULL);
	DispatchThreads(&threadCluster);
	{
		glutDisplayFunc(display);
		glutReshapeFunc(resize);
		glutMainLoop();
	}
	DestroyThreads(&threadCluster);
	FreeMeshs();
	FreeMaterials();

	delete pCamera;
	CGfxRenderer::Destroy();

	return 0;
}
