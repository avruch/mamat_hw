#ifndef IP_H
#define IP_H

#include "field.h"

#define MASK_SEGMENT 2
#define SEGMENTS 4

class Ip : public Field {
private:
    unsigned int low;
    unsigned int high;

public:
	~Ip();

    Ip(String pattern);
     /**
     * @brief put the relvent values to rule.
     * @return true if success 
     */
    bool set_value(String val);
     /**
     * @brief matching ip values to legal range
     * @return true if the value in range
     */
    bool match_value(String val) const;
};




#endif
