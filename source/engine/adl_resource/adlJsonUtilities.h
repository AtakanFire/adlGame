#ifndef adlJsonUtilities_h__
#define adlJsonUtilities_h__

#include <iostream>
#include <string>

#include <document.h>
#include <prettywriter.h>


class adlJsonUtilities { 

public:
	 
	adlJsonUtilities();
	~adlJsonUtilities();
	


	virtual void ReadFromJson();
	virtual void WriteToJson();

	template <typename T>
	void serialize(const std::string& valueName, const std::string& valueType, const T& value0, const T& value1, const T& value2);

	void serialize(const std::string& valueName, const std::string& valueType, bool isStart);

	// serialize(valueName, valueType, value)
	// deserialize(valueName, valueType, value)

private:

};

#endif //adlJsonUtilities_h__