#pragma once
//�ۺ����������rigidbody
class FPSRigidBodyMover : public MonoBehavour {
private:
	RigidBody *rid = NULL;
	double maxSpeed;
public:
	FPSRigidBodyMover(double maxSpeed) :maxSpeed(maxSpeed) {}
	void Awake() override {
		if (gameObject->rigidBody == NULL) {
			ShowWarnMessage("There is no rigidBody!!\nû�и����������", "����FPSRigidBodyMover���");
			gameObject->DestroyComponent(this);
		}
		else {
			rid = gameObject->rigidBody;
		}
	}
	void Update() override {
		double h = (Input::GetKey('d') ? 1 : 0) + (Input::GetKey('a') ? -1 : 0);
		double v = (Input::GetKey('w') ? 1 : 0) + (Input::GetKey('s') ? -1 : 0);
		double u = (Input::GetKey(KeyCode::Space) ? 1 : 0) + (Input::GetKey(KeyCode::LeftCtrl) ? -1 : 0);
		Vector3 vec(h, u, -v);

		if (Input::GetKeyDown(KeyCode::Esc)) {
			SetGameMode(false);
			exit(0);
		}
		if (Input::GetKeyDown('f')) {
			Input::SetFPSmode(!Input::FPSmode);
		}
		rid->SetVelocity(transform->GetWorldMatrix() ^ (vec * maxSpeed));
	}

};