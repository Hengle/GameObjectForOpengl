#pragma once
class Models {
private:
	static Models* list;
public:
	static Models* List() {
		if (list == NULL) {
			list = new Models();
		}
		return list;
	}
	//�����Ǳ���
	const  Model model1 = Model("nanosuit/nanosuit.obj");
};

Models* Models::list = NULL;