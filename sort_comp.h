#ifndef SORT_COMP_H_INCLUDED
#define SORT_COMP_H_INCLUDED

#define sortComp(func) {                                \
    const String* a =  (const String*)ap;               \
    const String* b =  (const String*)bp;               \
    int cmp_empty = (a->length == 0) - (b->length == 0); \
    if (cmp_empty == 0) {                               \
        return  func (a,b);                             \
    }                                                   \
    else{                                               \
        return cmp_empty;                               \
    }                                                   \
}



#endif
