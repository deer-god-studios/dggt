#ifndef _DGGT_MEM_BLK_H_

namespace dggt
{
	template <typename T,msize S>
	struct blk
	{
		T[S] mem;
		
		T& operator[](msize offset) { return mem[offset]; }
		const T& operator[](msize offset) const { return mem[offset]; }
		T& operator*() { return mem[0]; }
		const T& operator*() const { return mem[0]; }
	};
}

#define _DGGT_MEM_BLK_H_
#endif
