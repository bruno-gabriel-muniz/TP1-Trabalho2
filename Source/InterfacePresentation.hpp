/**
 * @file InterfacePresentation.hpp
 * @brief Interface de comunicação das UIs utilizada por @ref CtrState "CtrState".
 */

#include <memory>

class CtrState;

/**
 * @class PresentationInte
 * @brief Interface base das UIs para os estados utilizados por @ref CtrState "CtrState".
 */
class PresentationInte {
private:
    CtrState *context;

public:
    /**
     * @brief Executa a interface.
     * @return Retorna a próxima interface a ser executada.
     */
    virtual PresentationInte* run() = 0;

    /**
     * @brief Realiza a validação e executa a transição de estado no controle da interface.
     * @param request Novo estado da interface.
     */
    virtual void change(PresentationInte *request) = 0;

    virtual ~PresentationInte() = default;
};
