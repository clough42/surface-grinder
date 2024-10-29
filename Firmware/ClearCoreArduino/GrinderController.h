// GrinderController.h

#ifndef GRINDERCONTROLLER_H
#define GRINDERCONTROLLER_H

#include "GrinderModel.h"
#include "GrinderView.h"
#include "IUserActions.h"

class GrinderController : public IUserActions {
public:
    GrinderController(GrinderModel& model, GrinderView& view)
        : m_model(model), m_view(view)
    {}

    void Init();
    void Update();

    void EnterEstop() override;
    void ClearEstop() override;
	void CycleStart() override;
	void CycleStop() override;
	void SelectUnits(Units units) override;
	void SelectAxis(Axis axisSwitchPosition, int resolutionSwitchPosition) override;
	void Jog(int32_t clicks) override;
	void SetWorkOffset(Axis selectedAxis) override;

private:
    void UpdateDROs();
	void UpdateDRO(Axis axis);
    void UpdateResolutionAndAxisIndicators();

    int32_t ConvertToNm(int32_t units); // convert from (units * 2^5)
	int32_t ConvertToUnits(int32_t nanometers); // convert to (units * 2^5)

    GrinderModel& m_model;
    GrinderView& m_view;

    Units m_units = Units::INCHES;
	Axis m_selectedAxis;
    int m_resolutionSwitchPosition = 0;
    int32_t m_selectedResolution;
    int32_t m_droWorkOffsets[3] = { 0, 0, 0 };
    
};

#endif // GRINDERCONTROLLER_H
