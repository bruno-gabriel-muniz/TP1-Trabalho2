#include <memory>

class CtrState;

class PresentationInte{
    private:
        CtrState *context;
    public:
        virtual PresentationInte* run() = 0;
        virtual void change(PresentationInte *request, CtrState *ctx) = 0;
        virtual ~PresentationInte() = default;
};