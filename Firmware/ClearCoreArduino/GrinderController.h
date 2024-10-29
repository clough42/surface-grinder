// GrinderController.h

#ifndef GRINDERCONTROLLER_H
#define GRINDERCONTROLLER_H

#include "GrinderModel.h"
#include "GrinderView.h"
#include "GrinderViewController.h"

class GrinderController : public GrinderViewController {
public:
    GrinderController(GrinderModel& model, GrinderView& view)
        : m_model(model), m_view(view)
    {}

    void Init();
    void Update();

    void JogAxisNm(int selectedAxis, int jogAmountNm) override;
    void EnterEstop() override;
    void ClearEstop() override;

private:
    GrinderModel& m_model;
    GrinderView& m_view;
};

#endif // GRINDERCONTROLLER_H
