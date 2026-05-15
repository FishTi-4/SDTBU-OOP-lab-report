#include "SY1.h"

namespace COMMS
{
    Comms::Comms(std::string name, std::string phone, std::string email)
    {
        this->name = name;
        this->phone = phone;
        this->email = email;
        // this->address = address;
    };

    Comms* build(std::string name, std::string email, std::string phone)
    {
        std::regex mail(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
        std::regex ph(R"(^1[3-9]\d{9}$)");

        if (std::regex_match(email, mail) && std::regex_match(phone, ph) && !name.empty())
        {
            return new Comms(name, phone, email);
        }
        else
        {
            return nullptr;
        }
    }

}