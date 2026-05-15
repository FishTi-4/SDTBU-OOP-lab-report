#include "SY1.h"

namespace COMMS
{
    class Comms
    {
        public:
        std::string name;
        std::string phone;  
        std::string email;
        // std::string address;
        Comms(std::string name, std::string phone, std::string email);
    };
    
    Comms* build(std::string name, std::string email, std::string phone);
    
} // namespace comms;
