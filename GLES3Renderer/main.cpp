// ShadingSystem.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Renderer.h"


glm::mat4 scale;
std::vector<GLuint> materials;
std::vector<CMesh*> meshs;

float sh_red[9] = { 0.0 };
float sh_green[9] = { 0.0 };
float sh_blue[9] = { 0.0 };

GLuint screenWidth = 500;
GLuint screenHeight = 500;

void LoadMesh(const char *szMeshFileName)
{
	CMesh *pMesh = new CMesh;
	pMesh->Load(szMeshFileName);
	meshs.push_back(pMesh);
}

void FreeMeshs(void)
{
	for (GLuint index = 0; index < meshs.size(); index++) {
		delete meshs[index];
	}

	meshs.clear();
}

void LoadMaterial(const char *szMaterialFileName)
{
	GLuint materialid = materials.size();
	materials.push_back(materialid);
	CRenderer::GetInstance()->LoadMaterial(szMaterialFileName, materialid);
}

void LoadSkyBox(void)
{
	LoadMesh("./Mesh/SkyBox.mesh");
	LoadMaterial("SkyBox.material");
	CRenderer::GetInstance()->SetCameraLookat(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	if (FILE *pFile = fopen("./Mesh/Env.sh", "rb")) {
		fscanf(pFile, "%f %f %f %f %f %f %f %f %f", &sh_red[0],   &sh_red[1],   &sh_red[2],   &sh_red[3],   &sh_red[4],   &sh_red[5],   &sh_red[6],   &sh_red[7],   &sh_red[8]);
		fscanf(pFile, "%f %f %f %f %f %f %f %f %f", &sh_green[0], &sh_green[1], &sh_green[2], &sh_green[3], &sh_green[4], &sh_green[5], &sh_green[6], &sh_green[7], &sh_green[8]);
		fscanf(pFile, "%f %f %f %f %f %f %f %f %f", &sh_blue[0],  &sh_blue[1],  &sh_blue[2],  &sh_blue[3],  &sh_blue[4],  &sh_blue[5],  &sh_blue[6],  &sh_blue[7],  &sh_blue[8]);
		fclose(pFile);
	}

	CRenderer::GetInstance()->SetAmbientLight(sh_red, sh_green, sh_blue);
}

void LoadCar(void)
{
	LoadMesh("./Mesh/Car.mesh");
	LoadMaterial("Car.material");

	CRenderer::GetInstance()->SetCameraLookat(0.0f, 2.0f, 4.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
	scale = glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f));
}

void LoadCarIBL(void)
{
	LoadMesh("./Mesh/Car.mesh");
	LoadMaterial("CarIBL.material");
	
	CRenderer::GetInstance()->SetCameraLookat(0.0f, 2.0f, 4.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
	scale = glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f));
}

void LoadTank(void)
{
	LoadMesh("./Mesh/TankBody.mesh");
	LoadMaterial("TankBody.material");

	LoadMesh("./Mesh/TankTrack.mesh");
	LoadMaterial("TankTrack.material");

	CRenderer::GetInstance()->SetCameraLookat(0.0f, 4.5f, 8.0f, 0.0f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	scale = glm::scale(glm::mat4(), glm::vec3(100.0f, 100.0f, 100.0f));
}

void LoadSphere(const char *szMaterialFileName)
{
	glutReshapeWindow(200, 200);

	LoadMesh("./Mesh/Sphere.mesh");
	LoadMaterial(szMaterialFileName);

	CRenderer::GetInstance()->SetCameraLookat(0.0f, 0.0f, 2.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	scale = glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f));
}

void RenderSkyBox(void)
{
//	static float angle = 0.0f; angle += 0.5f;
//	CRenderer::GetInstance()->SetAmbientLight(sh_red, sh_green, sh_blue, glm::radians(angle), 0.0f, 1.0f, 0.0f);

	glm::mat4 scale = glm::scale(glm::mat4(), glm::vec3(5000.0f, 5000.0f, 5000.0f));
	glm::mat4 rotateX = glm::rotate(glm::mat4(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 transform = rotateX * scale;

	for (GLuint index = 0; index < min(1, materials.size()); index++) {
		meshs[index]->SetTransform(transform);
		CRenderer::GetInstance()->DrawInstance(materials[index], meshs[index]->GetVertexBuffer(), meshs[index]->GetIndexBuffer());
	}
}

void RenderMesh(void)
{
	static float angle = 45.0f; angle += 0.5f;
	glm::mat4 rotateX = glm::rotate(glm::mat4(), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotateY = glm::rotate(glm::mat4(), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 translate = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 transform = translate * rotateY * rotateX * scale;

	for (GLuint index = 1; index < materials.size(); index++) {
		meshs[index]->SetTransform(transform);
		CRenderer::GetInstance()->DrawInstance(materials[index], meshs[index]->GetVertexBuffer(), meshs[index]->GetIndexBuffer());
	}
}

void display(void)
{
	CRenderer::GetInstance()->SetViewport(0, 0, screenWidth, screenHeight);
	CRenderer::GetInstance()->Clear(0.1f, 0.1f, 0.1f, 1.0f, 1.0f);

	CRenderer::GetInstance()->SetCameraPerspective(60.0f, 1.0f, 0.1f, 100.0f);
	CRenderer::GetInstance()->SetDirectionLight(-1.0f, -1.0f, -1.0f, 3.0f, 3.0f, 3.0f);

	RenderSkyBox();
	RenderMesh();
	
	glutSwapBuffers();
}

void timer(int value)
{
	display();
	glutTimerFunc(30, timer, 0);
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
	glutTimerFunc(30, timer, 0);
	glewInit();

	CRenderer::Create("./Shader", "./Mesh", "./Mesh");
	LoadSkyBox();
//	LoadCar();
//	LoadCarIBL();
//	LoadTank();
//	LoadSphere("Car.material");
//	LoadSphere("CarIBL.material");
//	LoadSphere("TankBody.material");
	{
		glutDisplayFunc(display);
		glutReshapeFunc(resize);
		glutMainLoop();
	}
	FreeMeshs();
	CRenderer::Destroy();

	return 0;
}
