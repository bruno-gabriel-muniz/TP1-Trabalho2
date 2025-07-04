#pragma once

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
        string result;
    public:
        Result(string res = "Default") : result(res) {}
        string show() {return result;};
};

class ResultPass: public Result{
    public:
        ResultPass() : Result(string(37, '_') + "PASSOU" + string(37, '_')) {}
};

class ResultFail: public Result{
    public:
        ResultFail() : Result(string(37, '/') + "FALHOU" + string(37, '\\')) {}
};

// Classe base de testes
class Test{
    protected:
        string nameTest = "Default";
        TypeTest typeTest = TypeTest();
        string in = "Default";
        string expected = "Default";
        string out = "Default";
        Result result = Result();
    public:
        Test() {};

        virtual void exec() = 0; // Método que realiza o teste.
        
        void show(); // Método que mostra o resultado do teste
        
        void run() {
            exec();
            show();
        }; // Método que roda o teste  
};

inline void Test::show(){
    cout << "\n";
    // Nome do teste
    cout << nameTest << "\nTypeTest: " << typeTest.show() << ":\n\n";
    // Dados do teste
    cout << "In: " << in
         << " | Expected: " << expected
         << " | Out: " << out << "\n\n";
    // Resultado do teste
    cout << result.show() << "\n";
    cout << "\n"; 
    return;
}
