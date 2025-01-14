/*
 * DataTypeEnum.cpp
 *
 *  Created on: Nov 3, 2021
 *      Author: mballance
 */

#include <algorithm>
#include "vsc/dm/IContext.h"
#include "vsc/dm/impl/TaskIsTypeFieldRef.h"
#include "DataTypeEnum.h"
#include "ModelValOp.h"
#include "TypeExprRange.h"
#include "TypeExprRangelist.h"
#include "TypeExprVal.h"

namespace vsc {
namespace dm {

DataTypeEnum::DataTypeEnum(
		const std::string	&name,
		bool 				is_signed) :
				m_name(name), m_is_signed(is_signed), m_width(-1) {

}

DataTypeEnum::~DataTypeEnum() {
	// TODO Auto-generated destructor stub
}

void DataTypeEnum::initVal(ValRef &v) {

}

void DataTypeEnum::finiVal(ValRef &v) {

}

ValRef DataTypeEnum::copyVal(const ValRef &src) {
	return ValRef();
}

bool DataTypeEnum::addEnumerator(
			const std::string	&name,
			const IModelVal		*val) {
	std::unordered_map<std::string,ModelVal>::const_iterator it;

	if ((it=m_enum_val_m.find(name)) == m_enum_val_m.end()) {
		m_enum_val_m.insert({name, ModelVal(val)});

		return true;
	} else{
		// Already have an entry
		return false;
	}
}

ITypeExprRangelist *DataTypeEnum::getDomain() {
	if (!m_domain.get()) {
		TypeExprRangelist *rl = new TypeExprRangelist();
		m_width = 32; // TODO: should adjust dynamically later

		std::vector<const ModelVal *> values;

		for (std::unordered_map<std::string,ModelVal>::const_iterator
				it=m_enum_val_m.begin();
				it!=m_enum_val_m.end(); it++) {
			values.push_back(&it->second);
		}

		// Sort the values
		if (m_is_signed) {
			std::sort(
				values.begin(),
				values.end(), [](const ModelVal *v1, const ModelVal *v2) {
					return ModelValOp::slt_s(v1, v2);
				});
		} else {
			std::sort(
				values.begin(),
				values.end(), [](const ModelVal *v1, const ModelVal *v2) {
					return ModelValOp::ult_s(v1, v2);
				});
		}

		uint64_t max_v = values.back()->val_u();
		m_width = 0;
		do {
			max_v >>= 1;
			m_width += 1;
		} while (max_v);
		fprintf(stdout, "max=%lld width=%d\n", (long long int)values.back()->val_u(), m_width);

		// Ensure we avoid the accidental sign
		if (!m_is_signed) {
			m_width++;
		}

		// Now, collapse the values into compact ranges
		std::vector<const ModelVal *>::const_iterator it=values.begin();
		std::vector<const ModelVal *>::const_iterator start = it;
		ModelVal exp_n;

		while (it!=values.end()) {

			// Move ahead until next != prev+1
			std::vector<const ModelVal *>::const_iterator prev = it;
			it++;

			if (it != values.end()) {
				ModelValOp::add_s(
						&exp_n,
						*prev,
						1,
						32);

				// Check if
				if (!ModelValOp::eq_s(&exp_n, *it)) {
					// Create a range and move on
					TypeExprRange *rng = 0;

					if (start == prev) {
                        fprintf(stdout, "TODO: enum domain\n");
                        /*
                        ValData start_v;
						ModelVal start_v(*start);
						start_v.setBits(m_width);
						// Single-value range
						rng = new TypeExprRange(
								true,
								new TypeExprVal(&start_v),
								0);
                         */

					} else {
                        fprintf(stdout, "TODO: enum domain\n");
                        /*
						ModelVal start_v(*start);
						ModelVal prev_v(*prev);

						start_v.setBits(m_width);
						prev_v.setBits(m_width);

						// Extends start..prev
						rng = new TypeExprRange(
								false,
								new TypeExprVal(&start_v),
								new TypeExprVal(&prev_v));
                        */
					}
					rl->addRange(rng);

					start = it;
				}
			} else {
				TypeExprRange *rng = 0;

				// Have from start..prev to stick in a range
				if (start == prev) {
                    fprintf(stdout, "TODO: enum domain\n");
                    /*
					ModelVal start_v(*start);
					start_v.setBits(m_width);

					// Single-value range
					rng = new TypeExprRange(
							true,
							new TypeExprVal(&start_v),
							0);
                    */
				} else {
					// Extends start..prev
                    fprintf(stdout, "TODO: enum domain\n");
                    /*
					ModelVal start_v(*start);
					ModelVal prev_v(*prev);

					start_v.setBits(m_width);
					prev_v.setBits(m_width);

					rng = new TypeExprRange(
							false,
							new TypeExprVal(&start_v),
							new TypeExprVal(&prev_v));
                    */
				}
				rl->addRange(rng);
			}
		}
		m_domain = ITypeExprRangelistUP(rl);
	}

	return m_domain.get();
}

int32_t DataTypeEnum::getWidth() {
	if (m_width == -1) {
		getDomain();
	}
	return m_width;
}

IModelField *DataTypeEnum::mkRootField(
	IModelBuildContext	*ctxt,
	const std::string	&name,
	bool				is_ref) {
	IModelField *ret;
	
	if (is_ref) {
		ret = ctxt->ctxt()->mkModelFieldRefRoot(this, name);
	} else {
        ValRefInt val(0, false, 32);
		ret = ctxt->ctxt()->mkModelFieldRoot(this, name, val);
	}

	return ret;
}

IModelField *DataTypeEnum::mkTypeField(
		IModelBuildContext	*ctxt,
		ITypeField			*type,
        const ValRef        &val) {
	IModelField *ret;

	if (TaskIsTypeFieldRef().eval(type)) {
		ret = ctxt->ctxt()->mkModelFieldRefType(type);
	} else {
		ret = ctxt->ctxt()->mkModelFieldType(type, val);
	}

	return ret;
}

}
} /* namespace vsc */
