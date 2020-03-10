#ifndef _DGGT_COLL_DEFINES_H_

/// @brief Resolves to the number of elements in a stack array.
/// @warning Only works with arrays defined with the syntax: type arrayName[#]
#define ARRAY_COUNT(X) (sizeof((X)))/(sizeof((X)[0]))

#define _DGGT_COLL_DEFINES_H_
#endif


