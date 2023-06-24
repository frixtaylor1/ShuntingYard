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
#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H

#include <algorithm>

#include "./Token.h"

//-----------------------------------------------------------------------//

template <class type> using Vector = std::vector<type>;

//-----------------------------------------------------------------------//
//		LexicalAnalizer Class
//-----------------------------------------------------------------------//
class LexicalAnalizer
{
public:
	LexicalAnalizer(const String&& expression);

	void doLexemes();

	const Vector<String>& getLexemes() const
	{
		return m_lexemes;
	}
private:
	String m_expression;
	Vector<char> m_lexemesOperands;
	Vector<String> m_lexemes;
};

//-----------------------------------------------------------------------//
//		LexemeToken type
//		Union between a Lexeme & Token
//-----------------------------------------------------------------------//
struct LexemeToken
{
	LexemeToken(Token* token, const std::string_view value);
	LexemeToken(const LexemeToken& lexemeToken)
		:m_token(lexemeToken.m_token), m_value(lexemeToken.m_value)
	{}
	LexemeToken(LexemeToken&& lexemeToken)
		: m_token(lexemeToken.m_token), m_value(lexemeToken.m_value)
	{}
	Token* m_token;
	String m_value;
};

//-----------------------------------------------------------------------//
//		ShuntingYard Class
//-----------------------------------------------------------------------//
class ShuntingYard
{
public:
	static void parse(const Vector<LexemeToken>&& lexemesTokens);
	static void showExpressionInReversedPolishNotation();
	static void release()
	{
		m_parsed.clear();
	}

	static Vector<LexemeToken>& getReversedPolishNotationExpression()
	{
		return m_parsed;
	}
private:
	static Vector<LexemeToken> m_parsed;
};

//-----------------------------------------------------------------------//
//		SyntaxAnalizer Class
//-----------------------------------------------------------------------//
// The responsability of this class is Categorize the lexemes and give them a type.
// Anything that looks like an event handling architecture is going to act here
// for example:
//		TokenStuff, callbackStuff, etc...
//
class SyntaxAnalizer
{
public:
	SyntaxAnalizer(const Vector<String>& lexemes);
	~SyntaxAnalizer();
	
	void analize();
	void showRawExpression();

private:
	typedef void (*CallbackChar)(const String& input, char condition);
	typedef void (*CallbackConstChar)(const String& input, const char* condition);

	void internalAnalizeWithConstrains(const String& lexeme);
	void analizeLexeme(const String& lexeme, const char* condition, CallbackConstChar func);
	void analizeLexeme(const String& lexeme, char condition, CallbackChar func);

	void setConstrains(const Vector<const char*>& constrains);
public:
	void release()
	{
		m_lexemes.clear();
		m_lexemesTokens.clear();
	}

	void setLexemes(const Vector<String>& lexemes);

	const Vector<LexemeToken>& getLexemeTokens() const;
	Vector<LexemeToken>& getLexemeTokens();
	
private:
	Vector<String> m_lexemes;
	Vector<const char*> m_numbersConstrains;
	static Vector<LexemeToken> m_lexemesTokens;
};

#endif // SHUNTINGYARD_H