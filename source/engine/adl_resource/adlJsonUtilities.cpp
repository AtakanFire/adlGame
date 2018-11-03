#include "adlJsonUtilities.h"

adlJsonUtilities::adlJsonUtilities()
{

}

adlJsonUtilities::~adlJsonUtilities()
{

}

void adlJsonUtilities::ReadFromJson()
{

}

void adlJsonUtilities::WriteToJson()
{
}

template<typename T>
inline void adlJsonUtilities::serialize(const std::string& valueName, const std::string& valueType, const T & value0, const T & value1, const T & value2)
{
	//writer.String(valueName);


	if (valueType == "string")
	{
		//writer.String(value);

	}
	else if (valueType == "double")
	{
		//writer.Double(value);
	}
	else if (valueType == "uint")
	{
		//writer.Uint(value);
	}
	// ...

	if (valueType == "adlVec3")
	{
		//writer.StartArray();
		//writer.Double(value0);
		//writer.Double(value1);
		//writer.Double(value2);
		//writer.EndArray();

	}

}

void adlJsonUtilities::serialize(const std::string & valueName, const std::string & valueType, bool isStart)
{
	//writer.String(valueName);

	if (valueType == "object")
	{
		if (isStart)
		{
			//writer.StartObject();
		}
		else
		{
			//writer.EndObject();			
		}

	}
	else if (valueType == "array")
	{
		if (isStart)
		{
			//writer.StartArray();
		}
		else
		{
			//writer.EndArray();
		}

	}
}
