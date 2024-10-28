// Controller.h

#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {
public:
    virtual ~Controller() = default;
    virtual void JogAxisNm(int selectedAxis, int jogAmountNm) = 0;
    virtual void EnterEstop() = 0; 
    virtual void ClearEstop() = 0;
};

#endif // CONTROLLER_H

