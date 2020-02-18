#ifndef _DGGT_MEM_DEFINES_H_

#define BYTES(X) (X)
#define B(X) BYTES(X)
#define KILOBYTES(X) (1024ULL*(BYTES((X))))
#define KB(X) KILOBYTES(X)
#define MEGABYTES(X) (1024ULL*(KILOBYTES((X))))
#define MB(X) MEGABYTES(X)
#define GIGABYTES(X) (1024ULL*(MEGABYTES((X))))
#define GB(X) GIGABYTES(X)

#define PTR_TO(TYPE,NAME) TYPE NAME##_; TYPE* NAME = &NAME##_;
#define INIT_PTR_TO(TYPE,NAME,VALUE) TYPE NAME##_ = VALUE; TYPE* NAME = &NAME##_;

#define _DGGT_MEM_DEFINES_H_
#endif
