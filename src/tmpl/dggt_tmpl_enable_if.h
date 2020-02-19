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
		val_t val;

		val_if(val_t val) { this->val=val; }

		operator val_t() { return val; }
	};

	template <bool B,typename IF,typename OR>
	struct val_or:enable_or<B,IF,OR>
	{
		val_t val;

		val_or(val_t val) { this->val=val; }
		operator val_t() { return val; }
	};

	template <typename IF,typename OR>
	struct val_or<true,IF,OR>
	{
		val_t val;

		val_or(val_t val) { this->val=val; }
		operator val_t() { return val; }
	};

	template <bool B,u32 VAL=0>
	struct enable_u32_if
	{
	};

	template <u32 VAL=0>
	struct enable_u32_if<true,VAL>
	{
		static const u32 VAL;
	};


	template <bool B,u32 VAL=0>
	void init_u32_if(u32* val) { }

	template <u32 VAL=0>
	void init_u32_if<true,VAL>(u32* val) { *val=VAL; }

	template <bool B,u32 VAL=0>
	void init_u32_or(u32 val,u32* valOut) { *valOut=val; }

	template <u32 VAL=0>
	void init_u32_or<true,VAL>(u32 val,u32* valOut) { *valOut=VAL; }

	// TODO: not general.
	template <u32 S>
	struct member_val_or
	:enable_u32_if<S!=0,S>,val_if<S==0,u32>
	{
	};

	template <u32 S>
	void init_member_if(member_val_or<S>* m,u32 val)
	{
		if (S==0)
		{
			m->val=val;
		}
	}

	template <u32 S>
	u32 get_member_if(member_val_or<S>* m)
	{
		return S==0?m->val:S;
	}


}

#define _DGGT_TMP_ENABLE_IF_H_
#endif
