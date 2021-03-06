#include "utils.hpp"
#include "OracleDMLTraits.hpp"
#include "OracleDMLLexer.hpp"
#include "OracleDML.hpp"
#include "OracleDML_OracleDMLKeys.hpp"
#include "OracleDML_OracleDMLCommons.hpp"

#include <sys/types.h>

#include <iostream>
#include <sstream>
#include <fstream>

using namespace Antlr3BackendImpl;
using namespace std;

static    OracleDMLLexer*		    lxr;

int 
main	(int argc, char *argv[])
{
	if (argc < 2 || argv[1] == NULL)
	{
		Utils::processDir("./input"); // Note in VS2005 debug, working directory must be configured
	}
	else
	{
		int i;

		for (i = 1; i < argc; i++)
		{
			Utils::processDir(argv[i]);
		}
	}

	printf("finished parsing OK\n");	// Finnish parking is pretty good - I think it is all the snow

	return 0;
}

void parseFile(const char* fName, int fd)
{
	OracleSQLParserTraits::InputStreamType*    input;
	OracleSQLParserTraits::TokenStreamType*	tstream;
	OracleDML*			psr;

	string data = Utils::slurp(fName);
	std::cout << "== parsing =====================================================================" << std::endl
		  << data << std::endl
		  << "================================================================================" << std::endl;
	
	input	= new OracleSQLParserTraits::InputStreamType((const ANTLR_UINT8 *)data.c_str(),
							     antlr3::ENC_8BIT,
							     data.length(), //strlen(data.c_str()),
							     (ANTLR_UINT8*)fName);

	input->setUcaseLA(true);
	if (lxr == NULL)
	{
		lxr = new OracleDMLLexer(input);	    // javaLexerNew is generated by ANTLR
	}
	else
	{
		lxr->setCharStream(input);
	}

	// Our lexer is in place, so we can create the token stream from it
	// NB: Nothing happens yet other than the file has been read. We are just 
	// connecting all these things together and they will be invoked when we
	// call the parser rule. ANTLR3_SIZE_HINT can be left at the default usually
	// unless you have a very large token stream/input. Each generated lexer
	// provides a token source interface, which is the second argument to the
	// token stream creator.
	tstream = new OracleSQLParserTraits::TokenStreamType(ANTLR_SIZE_HINT, lxr->get_tokSource());

	// Finally, now that we have our lexer constructed, we can create the parser
	psr	    = new OracleDML(tstream);  // javaParserNew is generated by ANTLR3

	{
		auto ast = psr->seq_of_statements();
		std::cout << ast.tree->toStringTree() << std::endl;
		std::cout << "Root:" << ast.tree.get() << std::endl;
	}
	delete psr; 
	delete tstream; 
	delete lxr; lxr = NULL;
	delete input; 
}
