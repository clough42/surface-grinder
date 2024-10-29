#ifndef I_USER_ACTIONS_H
#define I_USER_ACTIONS_H

// Controller Interface for the View
//
// This interface defines the methods that the view can call on the controller.
// These are separated out into a separate interface to make it harder for
// the view to accidentally call methods that it shouldn't.
class IUserActions {
public:
    virtual ~IUserActions() = default;
    virtual void EnterEstop() = 0; 
    virtual void ClearEstop() = 0;
	virtual void CycleStart() = 0;
	virtual void CycleStop() = 0;
	virtual void SelectUnits(Units units) = 0;
	virtual void SelectAxis(Axis selectedAxis, int resolutionSwitchPosition) = 0;
    virtual void Jog(int32_t clicks) = 0;
	virtual void SetWorkOffset(Axis selectedAxis) = 0;
};

#endif // I_USER_ACTIONS_H

