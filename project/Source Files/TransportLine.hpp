#pragma once


class TransportLine {
private:
	int lineNum;
	char type;
public:
	TransportLine(int lineNumber, char typeOfLine);
	friend class Edge;
	bool operator==(const TransportLine& b) const;
};

