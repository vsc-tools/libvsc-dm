/*
 * Copyright 2019-2021 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * rand_attr.h
 *
 *  Created on: Aug 10, 2021
 *      Author: mballance
 */

#pragma once
#include "attr_cls.h"
#include "attr_scalar.h"
#include "enum_t.h"
#include "int_t.h"

namespace vsc {
namespace facade {

template <typename T> class rand_attr : public T {
public:
	rand_attr(const scope &name) : T(name) { }
};

template <int W> class rand_attr<ui_t<W>> : public attr_scalar {
public:
	friend class vec_scalar;

	rand_attr(
			const scope &name,
			const int_t	&ival=int_t(false, W, 0)) :
				attr_scalar(false, W, ival) {
		m_field->set_flag(ModelFieldFlag_DeclRand);
	}

	uint64_t operator ()() { return u32(); }

private:

	rand_attr(
			const scope 	&name,
			bool			parentless) :
		attr_scalar(false, W, int_t(false, W, 0), parentless) {
		m_field->set_flag(ModelFieldFlag_DeclRand);
	}
};

template <int W> class rand_attr<si_t<W>> : public attr_scalar {
public:

	rand_attr(
			const scope &name,
			const int_t &ival=int_t(true, W, 0)) :
				attr_scalar(true, W, ival) {
		m_field->set_flag(ModelFieldFlag_DeclRand);
	}

	int64_t operator ()() { return i64(); }
};

template <typename T, T first, T last> class rand_attr<enum_t<T, first, last>> : public attr_scalar {
public:

	rand_attr(
			const scope &name) : attr_scalar(true, 32, int_t(true, 32, 0)) { }

	T operator ()() { return reinterpret_cast<T>(i64()); }
};

template <> class rand_attr<int> : public attr_scalar {
public:

	rand_attr(
			const scope		&name,
			const int_t		&ival=int_t(true, 32, 0)) :
				attr_scalar(true, 32, ival) {
		m_field->set_flag(ModelFieldFlag_DeclRand);
	}

	int32_t operator ()() { return i32(); }
};

template <> class rand_attr<unsigned int> : public attr_scalar {
public:

	rand_attr(
			const scope		&name,
			const int_t		&ival=int_t(false, 32, 0)) :
				attr_scalar(false, 32, ival) {
		m_field->set_flag(ModelFieldFlag_DeclRand);
	}

	uint32_t operator ()() { return u32(); }
};

}
}
