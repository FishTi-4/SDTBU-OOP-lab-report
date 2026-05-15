#include "SY1.h"

namespace COMMENTRY
{
    class CommEntry{
        std::unordered_multiset<std::unique_ptr<COMMS::Comms>> commsList;
        public:
        bool add(std::string name, std::string email, std::string phone);
        bool dt(std::string name, std::string email, std::string phone);
    };
    
}