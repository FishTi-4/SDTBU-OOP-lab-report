#include "SY2.h"

namespace COMMS
{
    class Comms
    {
        public:
        std::string name;
        std::string phone;  
        std::string email;
        // std::string address;
        
        //构造
        Comms(std::string name, std::string phone, std::string email);
        
        //缺省构造
        Comms() = default;

        //析构
        ~Comms();
        
    };
    
    Comms* build(std::string name, std::string email, std::string phone);
    
} // namespace comms;
