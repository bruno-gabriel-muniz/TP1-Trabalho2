#include <iostream>

using namespace std;

// Classe que define o tipo de teste
class TypeTest{
    protected:
        string typeName;
    public:
        TypeTest(string typeName = "Default") : typeName(typeName) {} 
        string show() {return typeName;};
};

class ValidArgument : public TypeTest{
    public:
        ValidArgument() : TypeTest("ValidArgument") {}
};

class InvalidArgument : public TypeTest{
    public:
        InvalidArgument() : TypeTest("InvalidArgument") {}
};

// Classe que demonstra o resultado do teste
class Result{
    protected:
        string result = "Default";
    public:
        string show() {return result;};
};

class ResultPass: public Result{
    protected:
        string result = string(37, '_') + "PASSOU" + string(37, '_');
};

class ResultFail: public Result{
    protected:
        string result = string(37, '/') + "FALHOU" + string(37, '\\');
};

// Template da classe base de testes
template<typename In, typename Out, typename Expected>
class Test{
    private:
        string nameTest;
        TypeTest typeTest;
        In in;
        Expected expected;
        Out out;
        Result result;
    public:
        Test(string nameTest, const TypeTest &typeTest, const In &in, const Expected &expected, const Out &out) :
            nameTest(nameTest), typeTest(typeTest), in(in), expected(expected), out(out) {};

        virtual void exec() = 0; // Método que realiza o teste.

        string showIn() {return in;}; // Mostra a entrada do teste
        string showExpected() {return expected;}; // Mostra a saída esperada
        string showOut() {return out;}; // Mostra a saída do teste
        
        void show(); // Método que mostra o resultado do teste
        
        void run() {
            exec();
            show();
        }; // Método que roda o teste  
};

template<class In, class Out, class Expected> void Test<In, Out, Expected>::show(){
    cout << "\n";
    // Nome do teste
    cout << nameTest << ":\n";
    // Dados do teste
    cout << "TypeTest: " << typeTest.show()
         << "In: " << showIn()
         << "Expected: " << showExpected()
         << "Out: " << showOut() << "\n";
    // Resultado do teste
    cout << result.show() << "\n";
    cout << "\n"; 
    return;
}
