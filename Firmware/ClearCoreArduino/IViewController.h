#ifndef I_VIEW_CONTROLLER_H
#define I_VIEW_CONTROLLER_H

// Controller Interface for the View
//
// This interface defines the methods that the view can call on the controller.
// These are separated out into a separate interface to make it harder for
// the view to accidentally call methods that it shouldn't.
class IViewController {
public:
    virtual ~IViewController() = default;
    virtual void JogAxisNm(int selectedAxis, int jogAmountNm) = 0;
    virtual void EnterEstop() = 0; 
    virtual void ClearEstop() = 0;
};

#endif // I_VIEW_CONTROLLER_H

