#ifndef _DGGT_TMPL_ENABLE_IF_H_

namespace dggt
{
	template <bool B,typename T=void>
	struct enable_if
	{
	};

	template <typename T>
	struct enable_if<false,T>
	{
		typedef T type;
	};

	template <bool B,typename IF=void,typename OR=void>
	struct enable_or
	{
		typedef OR type;
	};

	template <typename IF,typename OR>
	struct enable_or<true,IF,OR>
	{
		typedef IF type;
	};

	template <bool B,typename T=u32>
	struct val_if:enable_if<B,T>
	{
		typedef T type;

		val_if(type val) { }

		operator type() { return type(); }
	};

	template <typename T>
	struct val_if<true,T>:enable_if<true,T>
	{
		typedef T type;
		type val;

		val_if(type val) { }

		operator type() { return val; }
	};

	template <bool B,typename IF,typename OR>
	struct val_or:enable_or<B,IF,OR>
	{
		OR val;

		val_or(OR val) { this->val=val; }
		operator OR() { return val; }
	};

	template <typename IF,typename OR>
	struct val_or<true,IF,OR>
	{
		IF val;

		val_or(IF val) { this->val=val; }
		operator IF() { return val; }
	};

	template <bool B,u32 VAL=0>
	struct enable_u32_if
	{
	};

	template <u32 VAL>
	struct enable_u32_if<true,VAL>
	{
		static const u32 val=VAL;
	};

	// TODO: not general.
	template <u32 S>
	struct member_val_or
	:enable_u32_if<S!=0,S>,val_if<S==0,u32>
	{
	};
}

#define _DGGT_TMP_ENABLE_IF_H_
#endif
