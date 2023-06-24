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

#include "./ShuntingYard.h"
#include "./TokenSubClass.h"

#include <iomanip>

#include <queue>
#include <stack>

//-----------------------------------------------------------------------//
//		LexicalAnalizer Class
//-----------------------------------------------------------------------//
LexicalAnalizer::LexicalAnalizer(const String&& expression)
	: m_expression(std::move(expression))
{
	m_lexemesOperands = { '+', '-', '*', '/', '(', ')', '[', ']', '{', '}', '^' };
}

void LexicalAnalizer::doLexemes()
{
    Vector<String> m_rawLexemes;
	m_rawLexemes.reserve(m_expression.length());

	std::string tmp = "";
    bool isOperand = false;

	for (auto& ch : m_expression)
	{
        Vector<char>::iterator it = find(m_lexemesOperands.begin(), m_lexemesOperands.end(), ch);
        if( it != m_lexemesOperands.end())
        {
            isOperand = true;
        }
		if (isOperand)
		{
			m_rawLexemes.emplace_back(tmp);
			tmp.clear();
			m_rawLexemes.emplace_back(" ");
			tmp += ch;
			m_rawLexemes.emplace_back(tmp);
			tmp.clear();
			
		}
		else
		{
			tmp += ch;
		}
	}

	m_lexemes.reserve(m_rawLexemes.size());
	for (auto& lexeme : m_rawLexemes)
	{
		if (lexeme != " ")
		{
			m_lexemes.emplace_back(lexeme);
		}
	}
}
//-----------------------------------------------------------------------//
//		LexemeToken type
//-----------------------------------------------------------------------//

LexemeToken::LexemeToken(Token* token, const std::string_view value)
: m_token(token), m_value(value)
{}

//-----------------------------------------------------------------------//
//		ShuntingYard Class implementation
//-----------------------------------------------------------------------//
void ShuntingYard::parse(const Vector<LexemeToken>&& lexemesTokens)
{
	std::queue<LexemeToken> m_outputQueue;
	std::stack<LexemeToken> m_operatorStack;

	for (auto& token : lexemesTokens)
	{
		if (token.m_token->isInCategory(TokenCategory::NumberToken))
		{
			m_outputQueue.emplace(std::move(token));
		}

		if (token.m_token->isInCategory(TokenCategory::OperatorToken))
		{
			if (!m_operatorStack.empty())
			{
				while (m_operatorStack.top().m_token->getPrecedence() > token.m_token->getPrecedence())
				{
					m_outputQueue.emplace(std::move(m_operatorStack.top()));
					m_operatorStack.pop();
				}
			}
			m_operatorStack.emplace(std::move(token));
		}

		if (token.m_token->isType(TokenTypes::ParenthesisOpenToken))
		{
			m_operatorStack.emplace(std::move(token));
		}

		if (token.m_token->isType(TokenTypes::ParenthesisCloseToken))
		{
			while (!m_operatorStack.top().m_token->isType(TokenTypes::ParenthesisOpenToken))
			{
				m_outputQueue.emplace(std::move(m_operatorStack.top()));
				m_operatorStack.pop();
			}
			m_operatorStack.pop();
		}
	}

	while (!m_operatorStack.empty())
	{
		m_outputQueue.emplace(std::move(m_operatorStack.top()));
		m_operatorStack.pop();
	}

	m_parsed.reserve(m_outputQueue.size());
	while (!m_outputQueue.empty())
	{
		m_parsed.push_back(std::move(m_outputQueue.front()));
		m_outputQueue.pop();
	}
}

void ShuntingYard::showExpressionInReversedPolishNotation()
{
	std::cout << std::setw(30) << "TOKEN NAME" << "\t\t" << "TOKEN VALUE" << "\t" << "TOKEN PRECEDENCE" << std::endl;
	std::cout << std::endl;

	for (auto& token : m_parsed)
	{
		std::cout << std::setw(30)
		<< token.m_token->getTokenName()
		<< "\t\t"
		<< "['"
		<< token.m_value
		<< "']"
		<< "\t\t"
		<< token.m_token->getPrecedence()
		<< std::endl;
	}
	std::cout << std::endl << std::endl;
}

Vector<LexemeToken> ShuntingYard::m_parsed;

//-----------------------------------------------------------------------//
//	SyntaxAnalizer Class
//-----------------------------------------------------------------------//
SyntaxAnalizer::SyntaxAnalizer(const Vector<String>& lexemes)
{
	setLexemes(lexemes);
	setConstrains({ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"});
}
SyntaxAnalizer::~SyntaxAnalizer()
{
}

void SyntaxAnalizer::analize()
{
	for (auto& lexeme : m_lexemes)
	{
		internalAnalizeWithConstrains(lexeme);
	}
}

void SyntaxAnalizer::showRawExpression()
{
	std::cout << std::setw(30) << "TOKEN NAME" << "\t\t" << "TOKEN VALUE" << "\t" << "TOKEN PRECEDENCE" << std::endl;
	std::cout << std::endl;

	for (auto& token : getLexemeTokens())
		std::cout << std::setw(30)
		<< token.m_token->getTokenName()
		<< "\t\t"
		<< "['"
		<< token.m_value
		<< "']"
		<< "\t\t"
		<< token.m_token->getPrecedence()
		<< std::endl;

	std::cout << std::endl << std::endl;
}

/*------------------------------------------------------------------------------------*/

static AddingOperator 		addingOperator;
static SubstractOperator 	substractOperator;
static DivideOperator 		divideOperator;
static MultiplyOperator 	multiplyOperator;
static IntegerTokenClass 	integerTokenClass;
static FloatTokenClass 		floatTokenClass;
static CurlyBraceOpen 		curlyBraceOpen;
static CurlyBraceClose 		curlyBraceClose;
static SquareBracketClose 	squareBracketClose;
static SquareBracketOpen 	squareBracketOpen;
static ParenthesisOpen 		parenthesisOpen;
static ParenthesisClose 	parenthesisClose;

/*------------------------------------------------------------------------------------*/

void SyntaxAnalizer::internalAnalizeWithConstrains(const String& lexeme)
{
	m_lexemesTokens.reserve(m_lexemes.size());
	// Operators...
	// Addition operator:
	analizeLexeme(lexeme, "+", [](const String& lexeme, const char* constrain) {
		if (lexeme == constrain)
		{
			m_lexemesTokens.emplace_back(&addingOperator, lexeme);
		}
	});

	// Substraction operator:
	analizeLexeme(lexeme, "-", [](const String& lexeme, const char* constrain) {
		if (lexeme == constrain)
		{
			m_lexemesTokens.emplace_back(&substractOperator, lexeme);
		}
	});

	// Divition operator:
	analizeLexeme(lexeme, "/", [](const String& lexeme, const char* constrain) {
		if (lexeme == constrain)
		{
			m_lexemesTokens.emplace_back(&divideOperator, lexeme);
		}
	});

	// Multiplication operator:
	analizeLexeme(lexeme, "*", [](const String& lexeme, const char* constrain) {
		if (lexeme == constrain)
		{
			m_lexemesTokens.emplace_back(&multiplyOperator, lexeme);
		}
	});

	//Numbers...
	int idx = 0;
	while (idx <= 9)
	{
		// Numbers 0 to 9 operator:
		analizeLexeme(lexeme, m_numbersConstrains[idx], [](const String& lexeme, const char* constrain) {
			if (lexeme == constrain)
			{
				m_lexemesTokens.emplace_back(&integerTokenClass, lexeme);
			}
		});
		idx++;
	}

	// Float Numbers...
	analizeLexeme(lexeme, '.', [](const String& lexeme, char constrain) {
		for (int idx = 0; idx < lexeme.length(); idx++)
		{
			if (lexeme[idx] == constrain)
			{
				m_lexemesTokens.emplace_back(&floatTokenClass, lexeme);
				break;
			}
		}
	});

	analizeLexeme(lexeme, "{", [](const String& lexeme, const char* constrain) {
		if (lexeme == constrain)
		{
			m_lexemesTokens.emplace_back(&curlyBraceOpen, lexeme);
		}
	});

	analizeLexeme(lexeme, "}", [](const String& lexeme, const char* constrain) {
		if (lexeme == constrain)
		{
			m_lexemesTokens.emplace_back(&curlyBraceClose, lexeme);
		}
	});

	analizeLexeme(lexeme, "[", [](const String& lexeme, const char* constrain) {
		if (lexeme == constrain)
		{
			m_lexemesTokens.emplace_back(&squareBracketClose, lexeme);
		}
	});

	analizeLexeme(lexeme, "]", [](const String& lexeme, const char* constrain) {
		if (lexeme == constrain)
		{
			m_lexemesTokens.emplace_back(&squareBracketClose, lexeme);
		}
	});

	analizeLexeme(lexeme, "(", [](const String& lexeme, const char* constrain) {
		if (lexeme == constrain)
		{
			m_lexemesTokens.emplace_back(&parenthesisOpen, lexeme);
		}
	});

	analizeLexeme(lexeme, ")", [](const String& lexeme, const char* constrain) {
		if (lexeme == constrain)
		{
			m_lexemesTokens.emplace_back(&parenthesisClose, lexeme);
		}
	});
}

void SyntaxAnalizer::analizeLexeme(const String& lexeme, const char* condition, CallbackConstChar func)
{
	func(lexeme, condition);
}

void SyntaxAnalizer::analizeLexeme(const String& lexeme, char condition, CallbackChar func)
{
	func(lexeme, condition);
}

void SyntaxAnalizer::setLexemes(const Vector<String>& lexemes)
{
	m_lexemes = lexemes;
}

void SyntaxAnalizer::setConstrains(const Vector<const char*>& constrains)
{
	m_numbersConstrains = constrains;
}
const Vector<LexemeToken>& SyntaxAnalizer::getLexemeTokens() const
{
	return m_lexemesTokens;
}
Vector<LexemeToken>& SyntaxAnalizer::getLexemeTokens()
{
	return m_lexemesTokens;
}

Vector<LexemeToken> SyntaxAnalizer::m_lexemesTokens;
