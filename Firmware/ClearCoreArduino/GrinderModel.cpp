// Copyright (c) 2024 James Clough (Clough42, LLC)
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "GrinderModel.h"

// Method to initialize all axes
void GrinderModel::Init() {
    m_leftLimit.Mode(Connector::INPUT_DIGITAL);
	m_rightLimit.Mode(Connector::INPUT_DIGITAL);
	m_currentCycle = nullptr;
	m_status = Status::IDLE;

	MotorMgr.MotorInputClocking(MotorManager::CLOCK_RATE_NORMAL);
	MotorMgr.MotorModeSet(MotorManager::MOTOR_ALL, Connector::CPM_MODE_STEP_AND_DIR);

    for (int i = 0; i < AXIS_COUNT; ++i) {
        m_axes[i].Init();
    }
}


void GrinderModel::Update() {
	// check for motor errors
	for (int i = 0; i < AXIS_COUNT; ++i) {
		if (m_axes[i].IsInError()) {
			// enter ESTOP if something has gone wrong
			EStop();
			break;
		}
	}

	// run the cycle, if one is in progress
	if (m_status == Status::RUN && m_currentCycle != nullptr) {
		bool moreToDo = m_currentCycle->Update();
		if (!moreToDo) {
			m_status = Status::IDLE;
			m_currentCycle = nullptr;
		}
	}
}

bool GrinderModel::CycleStart(Mode mode) {
	//// if a cycle is currently in hold, we should just return to the run state
	if (m_status == Status::HOLD && m_currentCycle != nullptr && m_currentCycle->IsForMode(mode)) {
		m_status = Status::RUN;
		return true;
	}

	// if we're idle, we need to start a new cycle
	if (m_status == Status::IDLE && m_currentCycle == nullptr) {
		for (int i = 0; i < m_cycleCount; ++i) {
			if (m_cycles[i]->IsForMode(mode)) {
				m_currentCycle = m_cycles[i];
				m_currentCycle->Reset();
				m_status = Status::RUN;
				return true;
			}
		}
	}

	// otherwise, there's nothing to do
	return false;
}

bool GrinderModel::CycleStop() {
	//// if a cycle is currently running, we should hold it
	if (m_status == Status::RUN && m_currentCycle != nullptr) {
		m_status = Status::HOLD;
		return true;
	}

	// if a cycle is currently in hold, we should terminate it
	if (m_status == Status::HOLD && m_currentCycle != nullptr) {
		m_status = Status::IDLE;
		m_currentCycle->Reset();
		m_currentCycle = nullptr;
	}

	return false;
}

int32_t GrinderModel::GetCurrentPositionNm(Axis axis) const {
	return m_axes[static_cast<int>(axis)].GetCurrentPositionNm();
}

bool GrinderModel::IsHomed() const {
	for (int i = 0; i < AXIS_COUNT; ++i) {
		if (!m_axes[i].IsHomed()) {
			return false;
		}
	}
	return true;
}

void GrinderModel::JogAxisNm(Axis axis, int32_t distanceInNanometers) {
	if (m_status == Status::IDLE) {
		m_axes[static_cast<int>(axis)].JogNm(distanceInNanometers);
	}
}

void GrinderModel::MoveAxisToPosition(Axis axis, int32_t positionInNanometers) {
	if (m_status == Status::IDLE) {
		m_axes[static_cast<int>(axis)].MoveToPositionNm(positionInNanometers);
	}
}

void GrinderModel::EStop() {
	m_status = Status::ESTOP;
	if (m_currentCycle != nullptr) {
		m_currentCycle->Reset();
		m_currentCycle = nullptr;
	}

	for (int i = 0; i < AXIS_COUNT; ++i) {
		m_axes[i].Disable();
	}
}


