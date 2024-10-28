// GrinderModel.h
#ifndef GRINDER_MODEL_H
#define GRINDER_MODEL_H

#include "MachineAxis.h"

class GrinderModel {
public:
    // Namespace to specify the axes
    enum Axis {
        X = 0,
        Y = 1,
        Z = 2
    };

    // Constructor that takes an array of three MachineAxis objects
    GrinderModel(MachineAxis* axes[3]);

    // Method to initialize all axes
    void Init();

    // Method to update all axes
    void Update();

	int32_t GetCurrentPositionNm(Axis axis) const {
		return m_axes[axis]->GetCurrentPositionNm();
	}

	void JogAxisNm(Axis axis, int32_t distanceInNanometers) {
		m_axes[axis]->JogNm(distanceInNanometers);
	}

	void ResetAndEnable() {
		for (int i = 0; i < 3; ++i) {
			m_axes[i]->ResetAndEnable();
		}
	}

private:
    MachineAxis* m_axes[3];
};

#endif // GRINDER_MODEL_H
