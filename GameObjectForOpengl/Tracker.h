#pragma once

/// <summary>
/// ƽ��׷��transform
/// </summary>
class Tracker : public MonoBehavour {
public:
	Transform *target;
	double smoothness;
	bool ifRotate;
	bool ifTranslate;

	void Update() override
	{
		if (ifTranslate) {
			//������lerp�Ż�
			transform->Translate((target->GetPosition() - transform->GetPosition())*(1 - smoothness), Space::World);
		}
		if (ifRotate)
		{
			transform->SetRotation(Quaternion::Slerp(
				transform->rotation,
				target->rotation,
				(1 - smoothness)
			));
		}
	}

	Tracker(Transform * target, double smoothness = 0.5, bool ifRotate = false, bool ifTranslate = true) :
		target(target), smoothness(smoothness), ifRotate(ifRotate), ifTranslate(ifTranslate)
	{

	}
};