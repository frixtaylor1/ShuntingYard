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
// #define __DEBUG__

#ifdef __DEBUG__
	static std::uint32_t s_allocations = 0;

	void* operator new(std::size_t size)
	{
		s_allocations++;
		std::cout << size << " bytes allocated\n";
		return malloc(size);
	}
#endif // __DEBUG__

int main()
{
	char expression[] = { "23+1/(9*2)+3*4" };

	LexicalAnalizer lexicalAnalizer(expression);
	lexicalAnalizer.doLexemes();

	SyntaxAnalizer syntaxAnalizer((Vector<String>&&)(lexicalAnalizer.getLexemes()));
	syntaxAnalizer.analize();
	syntaxAnalizer.showRawExpression();
	
	ShuntingYard::parse((Vector<LexemeToken>&&)(syntaxAnalizer.getLexemeTokens()));
	ShuntingYard::showExpressionInReversedPolishNotation();

	// ShuntingYard::getReversedPolishNotationExpression();

	syntaxAnalizer.release();

#ifdef __DEBUG__
	std::cout << s_allocations << " allocations" << std::endl;
#endif // __DEBUG__

	return 0;
}