#include "OpenglIndex.h"
#include "TransformIndex.h"
#include "ModelIndex.h"

#include "Shaders.h"
#include "Models.h"
#include "Textures.h"
#include "GameObjects.h"
#include "Components.h"

void SetScene() {

	mainScene.SetCamera(Vector3(0, 10, 30), Quaternion::identity);	//�������λ��
	mainScene.physicEngine.SetFloorParameters(0, 1);				//���õ������
	AddComponent(new MouseRotater(0.3f, 0.3f));
	AddComponent(new FPSMover());

	AddGameObject(new Ground("Ground", 0, 100, 100));

	AddGameObject(new Ball("Ball", 5, Vector3(10, 15, 0), Quaternion::identity));
	AddComponent(new RigidBody(5, 1));
	AddComponent(new SphereCollider(5, Vector3::zero, 1.01));
	AddComponent(new Gravity(30));
	//AddComponent(new LightComponent());

	AddGameObject(new Ball("Ball", 3, Vector3(0, 15, 9), Quaternion::identity));
	AddComponent(new RigidBody(5, 1));
	AddComponent(new SphereCollider(3, Vector3::zero, 1.01));
	AddComponent(new Gravity(30));
	AddComponent(new LightComponent());

	AddGameObject(new Ball("Ball", 3, Vector3(0, 15, 89), Quaternion::identity));
	AddComponent(new RigidBody(5, 1));
	AddComponent(new SphereCollider(3, Vector3::zero, 1.01));
	AddComponent(new Gravity(30));
	AddComponent(new LightComponent());

	AddGameObject(new ScaledTestModel("Model", Vector3::zero, Quaternion::identity, Vector3(0.003, 0.003, 0.003)));
	AddComponent(new mover());
}

void SetLight() {
	//�趨��һ����Դ����ƽ�й�
	LightData::num++;

	LightData::pos[0] = Vector3(0, 1, 0.4);	//��ķ���Ϊ������㵽ԭ��

	LightData::colors[0] = 1;
	LightData::colors[1] = 1;
	LightData::colors[2] = 1;
	LightData::colors[3] = 1;

	LightData::itensities[0] = 1;

	LightData::distanceSqrs[0] = 1;

	shadowMapShader = Shaders::List()->shadowMap.programId;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("ͼ��ѧ����");

	//glutGameModeString("1920x1080");
	//����ȫ��ģʽʱʹ�õķֱ���
	/*
	��ʽ����:
	��WxH:Bpp@Rr��
	W - ��Ļ��ȵ�����
	H - ��Ļ�߶ȵ�����
	Bpp - ÿ�����صı�����
	Rr - ��ֱˢ�µ�����, ��λ�Ǻ���(hz)

	�ڽ�����һ��֮ǰ, ע����Щ����ֻ������Ӳ��.���ָ����ģʽ�ǲ�����, ���ûᱻ����.
	����:
	"800x600:32@100" - ��Ļ��С800x600; 32λ��ɫ��; 100���� ��ֱˢ��
	"640x480:16@75" - ��Ļ��С640x480; 16λ��ɫ��; 75����

	�������ַ���ģ������������Ҫ��ȫ�������������:
	��WxH��
	��WxH : Bpp��
	��WxH@Rr��
	��@Rr��
	��:Bpp��
	��Bpp : @Rr��*/
	//SetGameMode(true);
	Initial();
	glutMainLoop();

	return 0;
}
