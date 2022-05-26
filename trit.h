#ifndef TRIT_H
#define TRIT_H

namespace termite
{
    // A trit contains a value of 0, 1 or -1.
    // Trits supports Kleene logic operators that are direct analogues to Boolean logic operators.
    
    class Trit
    {
    public:
        int val : 2; 

        Trit();
        
        Trit(int val);

        // Logical NOT
        Trit operator!() const;

        // Logical AND
        Trit operator&&(const Trit &b) const;

        // Logical OR
        Trit operator||(const Trit &b) const;

        // Logical XOR
        Trit operator^(const Trit &b) const;

        // Equality
        bool operator==(const Trit &b) const;

        // Inequality
        bool operator!=(const Trit &b) const;

        // Character representation for debugging purposes
        char charVal() const;

        static Trit fromChar(char chr);

        // Constants for the trits with values of 0, 1, and -1
        static const Trit ZERO;
        static const Trit ONE;
        static const Trit NEG;
    };
}

#endif