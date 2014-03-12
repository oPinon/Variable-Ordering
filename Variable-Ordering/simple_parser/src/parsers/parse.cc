#include <istream>

#include "parsers/bpn.hh"
#include "parsers/parse.hh"
#include "parsers/prod.hh"
#include "parsers/tina.hh"
#include "parsers/xml.hh"

namespace pnmc { namespace parsers {
  
/*------------------------------------------------------------------------------------------------*/

std::shared_ptr<pn::net>
parse(input_format format, std::istream& in)
{
  switch (format)
  {
    case (input_format::bpn)  : return parsers::bpn(in);
    case (input_format::prod) : return parsers::prod(in);
    case (input_format::tina) : return parsers::tina(in);
    case (input_format::xml)  : break;
  }
  return parsers::xml(in);
}

/*------------------------------------------------------------------------------------------------*/

}} // namespace pnmc::parsers
