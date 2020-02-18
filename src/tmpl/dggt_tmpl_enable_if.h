#ifndef _DGGT_TMPL_ENABLE_IF_H_

namespace dggt
{
	template <bool B,typename T=void>
	struct enable_if
	{
	};

	template <typename T=void>
	struct enable_if<false,T>
	{
		typedef T val_t;
	};

	template <bool B,typename IF=void,typename OR=void>
	struct enable_or
	{
		typedef OR val_t;
	};

	template <typename IF=void,typename OR=void>
	struct enable_or<true,IF,OR>
	{
		typedef IF val_t;
	};

	template <bool B,typename T=u32>
	struct val_if:enable_if<B,T>
	{
		typedef T val_t;
		val_if(val_t val) { }
		operator val_t() { return (val_t)this; }
	};

	template <typename T=u32>
	struct val_if:enable_if<true,T>
	{
		typedef T val_t;
		static val_t val;

		val_if(val_t val) { this->val=val; }

		operator val_t() { return val; }
	};

	template <bool B,typename IF,typename OR>
	struct val_or:enable_or<B,IF,OR>
	{
		static val_t val;

		val_or(val_t val) { this->val=val; }
		operator val_t() { return val; }
	};

	template <typename IF,typename OR>
	struct val_or<true,IF,OR>
	{
		static val_t val;

		val_or(val_t val) { this->val=val; }
		operator val_t() { return val; }
	};

	template <u32 VAL=0>
	struct enable_u32_if<true,VAL>
	{
		static const u32 VAL;

		operator u32() { return VAL; }
	};


	template <bool B,u32 VAL=0>
	void init_u32_if(u32* val) { }

	template <u32 VAL=0>
	void init_u32_if<true,VAL>(u32* val) { *val=VAL; }

	template <bool B,u32 VAL=0>
	void init_u32_or(u32 val,u32* valOut) { *valOut=val; }

	template <u32 VAL=0>
	void init_u32_or<true,VAL>(u32 val,u32* valOut) { *valOut=VAL; }
}

#define _DGGT_TMP_ENABLE_IF_H_
#endif
