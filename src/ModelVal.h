/*
 * ModelVal.h
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <stdint.h>
#include <vector>

namespace vsc {

class DataType;

class ModelVal;
using ModelValUP=std::unique_ptr<ModelVal>;
class ModelVal {
public:

	class iterator {
	public:
		friend class ModelVal;

		iterator();

		void append(uint32_t val);

	private:
		iterator(ModelVal *v, int32_t idx);

	private:
		ModelVal			*m_val;
		int32_t				m_idx;

	};

	class const_iterator {
	public:
		friend class ModelVal;

		const_iterator();

	private:
		const_iterator(ModelVal *v, int32_t idx);

	private:
		ModelVal			*m_val;
		int32_t				m_idx;
	};

public:
	ModelVal();

	ModelVal(DataType *type);

	virtual ~ModelVal();

	ModelVal::iterator begin();

	ModelVal::const_iterator begin() const;

private:
	DataType						*m_type;
	std::vector<uint32_t>			m_val;
};

} /* namespace vsc */
