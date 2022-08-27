#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

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

const int ARG_NOT_FOUND = -1;

int parseArg(int argc, const char* argv[], const char* arg_to_find);

bool isEnterExit(const char* a);

#endif // MAIN_H_INCLUDED
