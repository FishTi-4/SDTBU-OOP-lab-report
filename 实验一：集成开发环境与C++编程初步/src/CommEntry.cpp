#include "SY1.h"

namespace COMMENTRY
{

    bool CommEntry::add(std::string name, std::string email, std::string phone)
    {
        if (COMMS::build(name, email, phone) != nullptr)
        {
            commsList.insert(std::make_unique<COMMS::Comms>(name, phone, email));
            std::cout << "添加成功" << std::endl;
            return true;
        }
        else
        {
            std::cout << "邮箱或者手机号格式不正确" << std::endl;
            return false;
        }
    }

}