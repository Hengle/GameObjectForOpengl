#pragma once
enum Space {
	World,
	Self
};
//�������
class MonoBehaviour {
public:
	char* name;
	MonoBehaviour *next;
	GameObject *gameObject;
	Transform *transform;
	MonoBehaviour();
	virtual ~MonoBehaviour();
	//ÿһ֡������
	virtual void Update();
	//��Update�󱻵��ã������������/TODO:�ĳɶ�ʱ����
	virtual void FixedUpdate();
	//�ڼ������ʱ������
	virtual void Init();
	//��ʼ������
	virtual void Awake();
	//��ʼ������
	virtual void Start();
	//�������Ⱦ
	virtual void Render();
	virtual void OnDestroy();
};