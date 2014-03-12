#ifndef _PNMC_PARSERS_PARSE_HH_
#define _PNMC_PARSERS_PARSE_HH_

#include <iosfwd>
#include <memory>

#include "pn/net.hh"

namespace pnmc { namespace parsers {

/*------------------------------------------------------------------------------------------------*/

enum class input_format {bpn, prod, tina, xml};

/*------------------------------------------------------------------------------------------------*/

std::shared_ptr<pn::net>
parse(input_format,std::istream&);

/*------------------------------------------------------------------------------------------------*/

}} // namespace pnmc::parsers

#endif // _PNMC_PARSERS_PARSE_HH_
