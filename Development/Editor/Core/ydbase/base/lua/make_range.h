#pragma once

#include <base/config.h>
#include <base/lua/state.h>

namespace base { namespace lua {
	template <class T>
	int convert_to_lua(state* ls, const T& v);

	template <class F, class S>
	int convert_to_lua(state* ls, const std::pair<F, S>& v)
	{
		int nresult = 0;
		nresult += convert_to_lua(ls, v.first);
		nresult += convert_to_lua(ls, v.second);
		return nresult;
	}

	template <class Iterator>
	struct iterator
	{
		static int next(state* ls)
		{
			iterator* self = static_cast<iterator*>(ls->touserdata(lua_upvalueindex(1)));

			if (self->first_ != self->last_)
			{
				int nreslut = convert_to_lua(ls, *self->first_);
				++(self->first_);
				return nreslut;
			}
			else
			{
				ls->pushnil();
				return 1;
			}
		}

		static int destroy(state* ls)
		{
			static_cast<iterator*>(ls->touserdata(1))->~iterator();
			return 0;
		}

		iterator(const Iterator& first, const Iterator& last)
			: first_(first)
			, last_(last)
		{ }

		Iterator first_;
		Iterator last_;
	};

	template <class Iterator>
	int make_range(state* ls, const Iterator& first, const Iterator& last)
	{
		void* storage = ls->newuserdata(sizeof(iterator<Iterator>));
		ls->newtable();
		ls->pushcclosure(iterator<Iterator>::destroy, 0);
		ls->setfield(-2, "__gc");
		ls->setmetatable(-2);
		ls->pushcclosure(iterator<Iterator>::next, 1);
		new (storage) iterator<Iterator>(first, last);
		return 1;
	}

	template <class Container>
	int make_range(state* ls, const Container& container)
	{
		return make_range(ls, std::begin(container), std::end(container));
	}
}}
