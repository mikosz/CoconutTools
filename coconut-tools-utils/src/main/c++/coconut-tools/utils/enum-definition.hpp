#ifndef COCONUT_TOOLS_UTILS_ENUMDEFINITION_HPP_
#define COCONUT_TOOLS_UTILS_ENUMDEFINITION_HPP_

#include <boost/preprocessor/for.hpp>

#define CT_ENUM_DEFINITION(ENUM_NAME, ENUM_VALUES) \\
	class ENUM_NAME { \\
	public: \\
	\\
		enum { \\
			BOOST_PP_FOR()\\
		}; \\
	\\
	}; \\

#endif /* COCONUT_TOOLS_UTILS_ENUMDEFINITION_HPP_ */
