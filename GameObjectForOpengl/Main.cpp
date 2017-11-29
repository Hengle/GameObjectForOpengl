#include "OpenglIndex.h"
#include "TransformIndex.h"
#include "ModelIndex.h"

#include "Shaders.h"
#include "Models.h"
#include "GameObjects.h"
#include "Components.h"

void SetScene() {

	mainScene.SetCamera(Vector3(0, 1, 3), Quaternion::identity);

	GameObject *sun = AddGameObject(new GameObject("t1", Vector3(0, 0, -200), Quaternion::EulerY(180)));
	AddComponent(new RigidBody(30, 0.1));
	AddComponent(new MouseRotater(0.05f, 0.05f));
	AddComponent(new FPSRigidBodyMover(20));
	AddComponent(new SphereCollider(3, Vector3(0,-10,0), 1));
	AddComponent(new PressLToShowPosition());

	AddChild(new TestModel("t1", Vector3(0, -10, 0), Quaternion::EulerY(180)));
	AddComponent(new MouseRotater(0, 0.05f));
	mainScene.camera.AddComponent(new Tracker(&(sun->transform), 0.9, true, false));

	sun = sun->AddChild(new GameObject("camPos", Vector3(0, 0, 30), Quaternion::EulerY(180)));

	mainScene.camera.AddComponent(new Tracker(&(sun->transform), 0.9));

	AddGameObject(new Sun("t2", 6, Vector3(10, 0, -100), Quaternion::identity));
	AddComponent(new RigidBody());
	AddComponent(new SphereCollider(6));

	AddGameObject(new TestModel("Sun!"));
	AddComponent(new AutoRotate(Vector3(0, 12, 0)));//��ת�ٶ�
	AddComponent(new SphereCollider(4, Vector3::zero, 1));
	AddComponent(new LightComponent());


	AddChild(new GameObject("Sun's Son", Vector3(80, 0, 0), Quaternion::identity));
	AddComponent(new AutoRotate(Vector3(0, -5, 0)));//������ת�ٶ�


	AddChild(new GameObject("Earth's parent", Vector3(0, 0, 0), Quaternion::Euler(Vector3(0, 0, 30))));
	AddComponent(new AutoRotate(Vector3(0, 10, 0)));//��ת�ٶ�


	GameObject *earth = AddChild(new Earth("Earth"));
	AddComponent(new SphereCollider(5));
	//AddComponent(new PressLToShowPosition());
	AddComponent(new AutoRotate(Vector3(0, 60, 0)));//����ת�ٶ�

	AddChild(new Moon("Moon", 2, Vector3(20, 0, 0), Quaternion::Euler(Vector3(0, 0, 0))));
	//AddComponent(new PressLToShowPosition());
}

void SetLight() {
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHTING);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("�յ���ģ��");

	Initial();
	glutMainLoop();

	return 0;
}
