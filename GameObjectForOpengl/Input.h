#pragma once

class Input {
public:
	static bool FPSmode;
	static void SetFPSmode(bool b);
	static bool* keyHold;
	static bool* keyUp;
	static bool* keyDown;
	static int mouseXPos;//��ǰ���x����
	static int mouseYPos;//��ǰ���y����
	static int centerX;
	static int centerY;
	static bool isMouseDown;
	static bool GetKey(unsigned char key);
	static bool GetKeyDown(unsigned char key);
	static bool GetKeyUp(unsigned char key);
	static int GetMouseX();//����ƶ�����
	static int GetMouseY();//����ƶ�����
	static double GetAxisHorizontal();
	static double GetAxisVertical();
	static void SetLastMousePos(int x, int y);
	static void Init();
	static void Update();//ÿһ֡������
	static int mouseXCenterworld;//��ǰ���������Ļ����
	static int mouseYCenterworld;//��ǰ���������Ļ����
private:
	static int lastMouseX;
	static int lastMouseY;
	static double hAxis;//ˮƽAxis
	static double vAxis;//��ֱAxis
	static const double axisAcceleratingRate;//Axis���ٶ�
};
void KeyboardDown(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void SpecialKeyboardDown(int key, int x, int y);
void SpecialKeyboardUp(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void MouseMove(int x, int y);
//��ֵ
class KeyCode {
public:
	//normal <128
	static const char Space = (char)32;
	static const char Esc = (char)27;

	//special >=128
	static const char Up = (char)128;
	static const char Down = (char)129;
	static const char Left = (char)130;
	static const char Right = (char)132;
	static const char LeftShift = (char)133;
	static const char RightShift = (char)134;
	static const char LeftCtrl = (char)135;
	static const char RightCtrl = (char)136;
	static const char LeftAlt = (char)137;
	static const char RightAlt = (char)138;
};