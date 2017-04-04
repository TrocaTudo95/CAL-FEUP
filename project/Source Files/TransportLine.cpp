#include "TransportLine.hpp"

TransportLine::TransportLine(int lineNumber, char typeOfLine) : lineNum(lineNumber), type(typeOfLine) {}

bool TransportLine::operator==(const TransportLine & b) const
{
	return (this->lineNum == b.lineNum && this->type == b.type);
}


