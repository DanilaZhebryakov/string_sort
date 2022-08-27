#include <stdlib.h>
#include <stdio.h>
#include <mem.h>
#include <assert.h>

static void msort_( void* m,int elcnt,int elsize,int (*cmp)(const void*,const void*),void* buffer) {
    if (elcnt == 1) {
        return;
    }

    void* m_half   = m + ((elcnt/2) * elsize);
    void* m_end    = m +   elcnt    * elsize ;
    msort_(m     ,  elcnt/2    , elsize, cmp, buffer);
    msort_(m_half, (elcnt+1)/2 , elsize, cmp, buffer);

    void* m_ptr1     = m;
    void* m_ptr2     = m_half;
    void* buffer_ptr = buffer;
    while (m_ptr1 < m_half && m_ptr2 < m_end){
        if (cmp( m_ptr1, m_ptr2) < 0) {
            memcpy(buffer_ptr, m_ptr1, elsize);
            m_ptr1 += elsize;
        }
        else{
            memcpy(buffer_ptr, m_ptr2, elsize);
            m_ptr2 += elsize;
        }
        buffer_ptr += elsize;
    }
    while(m_ptr1 < m_half){
        memcpy(buffer_ptr, m_ptr1, elsize);
        m_ptr1 += elsize;
        buffer_ptr += elsize;
    }
    while(m_ptr2 < m_end){
        memcpy(buffer_ptr, m_ptr2, elsize);
        m_ptr2 += elsize;
        buffer_ptr += elsize;
    }
    memcpy(m,buffer,elcnt*elsize);
}
//! sorts an array using merge sort. Params fully match params of standard qsort()
void msort( void* m, int elcnt, int elsize, int (*cmp)(const void*, const void*)) {
    void* buffer = malloc(elsize*elcnt);
    assert(buffer != nullptr);
    msort_(m, elcnt, elsize, cmp, buffer);
    free(buffer);
}

