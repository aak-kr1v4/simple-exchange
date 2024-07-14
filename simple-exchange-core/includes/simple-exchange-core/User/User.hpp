#ifndef USER_HPP
#define USER_HPP

#include "types/allTypes.hpp"

class User
{
    public:
        User();
        User(const std::string& aName);
        User(const std::string& aName, size_t aId);

    public:
        std::string     getName     () const;
        void            setName     (const std::string& aName);

        size_t          getId       () const; 
        void            setId       (size_t aId);

        void            setBalance  (CUR_T aCurType, ldouble aAmount);
        ldouble         getBalance  (CUR_T aCurType) const;

    private:
        size_t          mId;
        std::string     mName;
        balance_map_t   mBalances;
};

#endif