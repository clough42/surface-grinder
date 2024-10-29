#ifndef I_VIEW_CONTROLLER_H
#define I_VIEW_CONTROLLER_H

class IViewController {
public:
    virtual ~IViewController() = default;
    virtual void JogAxisNm(int selectedAxis, int jogAmountNm) = 0;
    virtual void EnterEstop() = 0; 
    virtual void ClearEstop() = 0;
};

#endif // I_VIEW_CONTROLLER_H

