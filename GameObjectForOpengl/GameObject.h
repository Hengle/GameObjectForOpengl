#pragma once
extern int vectorNum;
class Vector3;
class Transform;
class MonoBehavour;
class GameObject;
class Scene;
//��λ����
class Vector3 {
public:
	float x, y, z;
	Vector3(float x, float y, float z);
	Vector3();
	Vector3& operator=(Vector3& rhs);
	Vector3& operator=(Vector3* rhs);
	Vector3& operator+=(Vector3& rhs);
	Vector3& operator+=(Vector3* rhs);
	Vector3 operator+ (Vector3& rhs);
	Vector3 operator+ (Vector3* rhs);
	Vector3& operator-=(Vector3& rhs);
	Vector3 operator- (Vector3& rhs);
	Vector3 operator* (float rhs);
	Vector3 operator/ (float rhs);
	Vector3& operator*=(float rhs);
	Vector3& operator/=(float rhs);
};

//�任���
class Transform {
public:
	Vector3 position;
	Vector3 rotation;
	Transform();
	Transform(Vector3* pos, Vector3* rot);
	~Transform();
	void Translate(Vector3& transition);
	void Translate(float x, float y, float z);
	void Rotate(Vector3& rot);
	void Rotate(float x, float y, float z);

	//�������ɱ����Ҫд�������ء�����
	Vector3 forward();
	Vector3 right();
	Vector3 up();
};


//�������
class MonoBehavour {
public:
	char* name;
	MonoBehavour *next;
	GameObject *gameObject;
	Transform *transform;
	MonoBehavour();
	virtual ~MonoBehavour();
	//ÿһ֡������
	virtual void Update();
	//�ڼ������ʱ������
	virtual void Awake();
	//��ʼ������
	virtual void Start();
	virtual void OnDestroy();
};

//��Ϸ����
class GameObject {
public:
	GameObject* parent;
	GameObject* child;
	GameObject* next;

	Transform transform;

	MonoBehavour* componentsPointer;

	//���캯��
	GameObject(Vector3& position, Vector3& rotation);
	GameObject(Vector3* position, Vector3* rotation);
	GameObject(Vector3& position, Vector3* rotation);
	GameObject();
	~GameObject();
	//��Ⱦ
	virtual void Render();
	void SetParent(GameObject *parent);
	GameObject* AddChild(GameObject *child);

	//������
	void AddComponent(MonoBehavour* component);
private:
	//���ø��ӹ�ϵ
	static void SetParent(GameObject* parent, GameObject* child);
	//ɾ����һ�����
	void PopComponent();
};

//����
class Scene {
public:
	GameObject *root;
	GameObject camera;
	CSkyBox skyBox;
	Scene();
	~Scene();
	void Render();
	void SetCamera(Vector3* pos, Vector3 *rot);
	GameObject* AddGameObject(GameObject* g);
	//�ݻ����弰��������
	void Destroy(GameObject* g);
	//�ݻ����弰��ͬ������
	void DestroyLayer(GameObject* g);
	void Awake();
	void Start();
	void Update();
private:
	void Awake(GameObject* g);
	void Start(GameObject* g);
	void Update(GameObject* g);
	void RenderGameObjects(GameObject* g);
};