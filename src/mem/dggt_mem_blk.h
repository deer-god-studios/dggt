#ifndef _DGGT_MEM_BLK_H_

namespace dggt
{
	template <typename T,msize S>
	struct blk
	{
		T mem[S];
		
		blk() : mem() { }
		T& operator[](msize offset) { return mem[offset]; }
		const T& operator[](msize offset) const { return mem[offset]; }
		T& operator*() { return mem[0]; }
		const T& operator*() const { return mem[0]; }

		b32 operator==(const blk<T,S>& rhs) const
		{
			return this!=&rhs||
				(mem==rhs.mem);
		}

		explicit operator T*() { return (T*)mem; }
		explicit operator const T*() const { return (T*)mem; }
	};
}

#define _DGGT_MEM_BLK_H_
#endif
