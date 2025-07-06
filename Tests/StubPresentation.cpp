#include "Source/InterfacePresentation.hpp"
#include "Source/CtrState.hpp"

class StubPresentation : public PresentationInte{
    public:
        StubPresentation(CtrState *ctx) {context = ctx;}
        PresentationInte* run(){return nullptr;}
        void change(PresentationInte *request) {context->setState(request);}
};
