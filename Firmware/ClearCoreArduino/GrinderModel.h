// GrinderModel.h
#ifndef GRINDER_MODEL_H
#define GRINDER_MODEL_H

#include "MachineAxis.h"

class GrinderModel {
public:
    // Constructor that takes an array of three MachineAxis objects
    GrinderModel(MachineAxis* axes[3], DigitalInOut& leftLimit,	DigitalInOut& rightLimit);

    // Method to initialize all axes
    void Init();

    // Method to update all axes
    void Update();

    int32_t GetCurrentPositionNm(Axis axis) const {
		return m_axes[static_cast<int>(axis)]->GetCurrentPositionNm();
	};

	void JogAxisNm(Axis axis, int32_t distanceInNanometers) {
		m_axes[static_cast<int>(axis)]->JogNm(distanceInNanometers);
	}

	void ResetAndEnable() {
		for (int i = 0; i < 3; ++i) {
			m_axes[i]->ResetAndEnable();
		}
	}

private:
    MachineAxis* m_axes[3];
	DigitalInOut& m_leftLimit;
	DigitalInOut& m_rightLimit;
};

#endif // GRINDER_MODEL_H
