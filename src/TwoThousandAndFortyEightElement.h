#ifndef TWOTHOUSANDANDFORTYHEIGHTELEMENT_H
#define TWOTHOUSANDANDFORTYHEIGHTELEMENT_H


#include<string>
#include<iostream>


class TwoThousandAndFortyEightElement
{
public :
    TwoThousandAndFortyEightElement(std::string t = "0", bool f = false) : p_text(t), p_fusionned(f) {}
    std::string text() const { return p_text; }
    bool isFusionned() const { return p_fusionned; }

protected :
    std::string p_text;
    bool p_fusionned;

    friend std::ostream& operator <<(std::ostream& out, const TwoThousandAndFortyEightElement& e){
        return out << e.text();
    }
};


#endif
