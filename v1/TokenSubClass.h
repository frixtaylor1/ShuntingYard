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

#ifndef TOKENSUBCLASS_H
#define TOKENSUBCLASS_H

#include "Token.h"

//-----------------------------------------------------------------------//
//		 AbstractClass OperatorTokenClass specification...
//-----------------------------------------------------------------------//
AbstractClass OperatorTokenClass : extends Token
{
public:
	CATEGORY_TOKEN(OperatorToken)
private:
};

class AddingOperator : implement OperatorTokenClass
{
public:
	TOKEN_TYPE(AddingOperatorToken)
	
	std::size_t getPrecedence() const
	{
		return 2;
	}
private:
};

class SubstractOperator : implement OperatorTokenClass
{
public:
	TOKEN_TYPE(SubstractOperatorToken)

	std::size_t getPrecedence() const
	{
		return 2;
	}
private:
};

class DivideOperator : implement OperatorTokenClass
{
public:
	TOKEN_TYPE(DivideOperatorToken)

	std::size_t getPrecedence() const
	{
		return 3;
	}
private:
};

class MultiplyOperator : implement OperatorTokenClass
{
public:
	TOKEN_TYPE(MultiplyOperatorToken)

	std::size_t getPrecedence() const
	{
		return 3;
	}
private:
};

//-----------------------------------------------------------------------//
//		 AbstractClass NumberTokenClass specification...
//-----------------------------------------------------------------------//
AbstractClass NumberTokenClass : extends Token
{
public:
	CATEGORY_TOKEN(NumberToken)
private:
};

class IntegerTokenClass : implement NumberTokenClass
{
public:
	TOKEN_TYPE(IntegerToken)
private:
};

class FloatTokenClass : implement NumberTokenClass
{
public:
	TOKEN_TYPE(FloatToken)
private:
};

//-----------------------------------------------------------------------//
//		 AbstractClass BlockClosureTokenClass specification...
//-----------------------------------------------------------------------//
AbstractClass BlockClosureTokenClass : extends Token
{
public:
	CATEGORY_TOKEN(BlockClosureToken)
private:
};

class CurlyBraceOpen : implement BlockClosureTokenClass
{
public:
	TOKEN_TYPE(CurlyBraceCloseToken)
private:
};

class CurlyBraceClose : implement BlockClosureTokenClass
{
public:
	TOKEN_TYPE(CurlyBraceCloseToken)
private:
};

class SquareBracketOpen : implement BlockClosureTokenClass
{
public:
	TOKEN_TYPE(SquareBracketOpenToken)
private:
};

class SquareBracketClose : implement BlockClosureTokenClass
{
public:
	TOKEN_TYPE(SquareBracketCloseToken)
private:
};

class ParenthesisOpen : implement BlockClosureTokenClass
{
public:
	TOKEN_TYPE(ParenthesisOpenToken)
private:
};

class ParenthesisClose : implement BlockClosureTokenClass
{
public:
	TOKEN_TYPE(ParenthesisCloseToken)
private:
};

#endif // TOKENSUBCLASS_H