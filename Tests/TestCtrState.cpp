#include <future>
#include <chrono>

#include "Tests/Test.hpp"
#include "Tests/StubPresentation.cpp"

#include "Source/CtrState.hpp"

using namespace std;

class TestCtrStateRun : public Test
{
public:
    void exec(){
        // Definindo os dados do teste.
        nameTest = "Teste->CtrState->Run";
        typeTest = ValidArgument();
        in = "StubPresentation";
        expected = "void -> in less 0.5 seconds";

        // Rodando o teste.
        CtrState *ctrState = new CtrState();
        StubPresentation *stub = new StubPresentation(ctrState);
        ctrState->setState(stub);

        try{ //Definindo o Time Out
            auto future = std::async(std::launch::async, [&]() {
                ctrState->run();
            });
            if (future.wait_for(std::chrono::milliseconds(500)) == future_status::ready) {
                // Função terminou no tempo esperado
                out = "void -> in less 0.5 seconds";
                result = ResultPass();
            } else {
                // Timeout ocorreu
                out = "timeout -> took more than 0.5 seconds";
                result = ResultFail();
            }
        } catch (...){
            out = "exception thrown";
            result = ResultFail();
        };
        delete ctrState;
        delete stub;
    }
};
