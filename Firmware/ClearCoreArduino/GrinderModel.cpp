// GrinderModel.cpp
#include "GrinderModel.h"

// Constructor implementation
GrinderModel::GrinderModel(MachineAxis* axes[3]) {
    for (int i = 0; i < 3; ++i) {
        m_axes[i] = axes[i];
    }
}

// Method to initialize all axes
void GrinderModel::Init() {
    for (int i = 0; i < 3; ++i) {
        m_axes[i]->Init();
    }
}

// Method to update all axes
void GrinderModel::Update() {
    for (int i = 0; i < 3; ++i) {
        // Add any update logic if needed
    }
}

