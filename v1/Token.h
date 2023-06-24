//
//	Contact: kevinmusic123@gmail.com
//	
//	MIT LICENSE:
//	
//	Copyright 2023 Kevin Daniel Taylor
//	Permission is hereby granted, free of charge, to any person obtaining a copy of this 
//	software and associated documentation files (the "Software"), to deal in the Software
//	without restriction, including without limitation the rights to use, copy, modify, merge,
//	publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to
//	whom the Software is furnished to do so, subject to the following conditions:
//	
//	The above copyright notice and this permission notice shall be included in all copies or
//	substantial portions of the Software.
//	
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
//	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
//	IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//	SOFTWARE.
//

#ifndef TOKEN_H
#define TOKEN_H

#include "./Core.h"

enum TokenCategory
{
	None = 0,
	
	OperatorToken 		= 1,
	NumberToken 		= 2,
	FunctionToken 		= 3,
	BlockClosureToken 	= 4
};

enum TokenTypes
{
	// Operators
	AddingOperatorToken	= 1,
	SubstractOperatorToken,
	DivideOperatorToken,
	MultiplyOperatorToken,

	// Numbers
	IntegerToken,
	FloatToken,

	// BlockClosures
	CurlyBraceOpenToken,
	CurlyBraceCloseToken,
	ParenthesisOpenToken,
	ParenthesisCloseToken,
	SquareBracketOpenToken,
	SquareBracketCloseToken
};


//-----------------------------------------------------------------------//
//		 Interface IToken specification...
//-----------------------------------------------------------------------//
interface IToken
{
	Abstract ~IToken() {}
	Abstract TokenTypes getType() const = 0;
	Abstract const char* getTokenName() const = 0;
	Abstract bool isType(const TokenTypes& type) = 0;
	Abstract TokenCategory getCategory() const = 0;
	Abstract const char* getCategoryName() const = 0;
};

//-----------------------------------------------------------------------//
//		 AbstractClass Token specification...
//-----------------------------------------------------------------------//
AbstractClass Token : extends IToken
{
public:
	Abstract ~Token() {}

	bool isInCategory(const TokenCategory& category)
	{
		return getCategory() & category;
	}
	virtual std::size_t getPrecedence() const
	{
		return 0;
	}
private:
};

#define CATEGORY_TOKEN(category) \
	TokenCategory getCategory() const \
	{ \
		return TokenCategory::category; \
	} \
	const char* getCategoryName() const \
	{ \
		return #category; \
	}

#define TOKEN_TYPE(type) \
	TokenTypes getType() const \
	{ \
		return type; \
	} \
	virtual bool isType(const TokenTypes& type) \
	{ \
		return type == getType(); \
	} \
	virtual const char* getTokenName() const \
	{ \
		return #type; \
	}

#endif // TOKEN_H
