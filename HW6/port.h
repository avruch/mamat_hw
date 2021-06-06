#ifndef PORT_H 
#define PORT_H

#include "field.h"

class Port : public Field {
private:
    int range[2];
public:
	~Port();
    Port(String pattern);
    /**
     * @brief put the relvent values to rule.
     * @return true if success 
     */
    bool set_value(String val);
    /**
     * @brief matching port values to legal range
     * @return true if the value in range
     */
    bool match_value(String val) const;
};

#endif
