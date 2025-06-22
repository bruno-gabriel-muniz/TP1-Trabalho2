#include <memory>

class CtrState;

/**
 * @class PresentationInte
 * @brief Interface base da UI para os estados usados por @ref CtrState "CtrState".
 */
class PresentationInte{
    private:
        CtrState *context;
    public:
        /**
         * @brief Roda a interface.
         * @return Retorna a próxima interface.
         */
        virtual PresentationInte* run() = 0;
        /**
         * @brief Faz a validação e troca as interfaces no controle de estado.
         * @param request Novo estado da interface.
         */
        virtual void change(PresentationInte *request) = 0;
        virtual ~PresentationInte() = default;
};