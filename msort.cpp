#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

static void msort_( void* m, size_t elcnt, unsigned int elsize, int (*cmp)(const void*, const void*), uint8_t* buffer) {
    if (elcnt == 1) {
        return;
    }

    uint8_t* m_half   = ((uint8_t*)m) + ((elcnt/2) * elsize);
    uint8_t* m_end    = ((uint8_t*)m) +   elcnt    * elsize ;

    msort_(       m     ,  elcnt/2    , elsize, cmp, buffer);
    msort_((void*)m_half, (elcnt+1)/2 , elsize, cmp, buffer);

    uint8_t* m_ptr1     = (uint8_t*)m;
    uint8_t* m_ptr2     = (uint8_t*)m_half;
    uint8_t* buffer_ptr = (uint8_t*)buffer;

    while (m_ptr1 < m_half && m_ptr2 < m_end){
        if (cmp( m_ptr1, m_ptr2) < 0) {
            memcpy(buffer_ptr, m_ptr1, elsize);
            m_ptr1 += elsize;
        }
        else {
            memcpy(buffer_ptr, m_ptr2, elsize);
            m_ptr2 += elsize;
        }
        buffer_ptr += elsize;
    }

    while (m_ptr1 < m_half) {
        memcpy(buffer_ptr, m_ptr1, elsize);
        m_ptr1 += elsize;
        buffer_ptr += elsize;
    }
    while (m_ptr2 < m_end) {
        memcpy(buffer_ptr, m_ptr2, elsize);
        m_ptr2 += elsize;
        buffer_ptr += elsize;
    }

    memcpy(m, buffer, elcnt*elsize);
}
//! sorts an array using merge sort. Params fully match params of standard qsort()
void msort( void* m, size_t elcnt, unsigned int elsize, int (*cmp)(const void*, const void*)) {
    uint8_t* buffer = (uint8_t*)malloc(elsize*elcnt);
    assert(buffer != nullptr);
    msort_(m, elcnt, elsize, cmp, buffer);
    free(buffer);
}

