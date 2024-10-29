// GriderViewController.h

#ifndef GRINDER_VIEW_CONTROLLER_H
#define GRINDER_VIEW_CONTROLLER_H

class GrinderViewController {
public:
    virtual ~GrinderViewController() = default;
    virtual void JogAxisNm(int selectedAxis, int jogAmountNm) = 0;
    virtual void EnterEstop() = 0; 
    virtual void ClearEstop() = 0;
};

#endif // GRINDER_VIEW_CONTROLLER_H

