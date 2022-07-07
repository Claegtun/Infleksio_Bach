//Libraries:
#include <iostream> //cout
#include <fstream> //files
#include <string> //string
#include <sstream> //stringstream
#include <vector> //vector

#include "ASTNode.hpp" //ASTNode, Verb, Noun
#include "functions.hpp" //functions
#include "Lexer.hpp" //Lexer
#include "Parser.hpp" //Parser
#include "Token.hpp" //Token

using namespace std;

void run(void);
const string normalise(ifstream&);

int main() {
    run();

    cout << "£" << endl;

    return 0;
}

void run() {
    //Open the input file.
    ifstream ifs("input.txt");
    if (!ifs.is_open()) {
        cout << "Error: 'input.txt' could not be opened." << endl;
        return;
    }

    //Open the output file.
    ofstream ofs("output.txt");

    //Declare the stringstream.
    stringstream ss("");

    //Declare local variables.
    string text;

    //Reformat the stream into a string without newlines and with spaces around stops and commas.
    text = normalise(ifs);
    cout << endl << "Done: " << text << ":" << endl;

    Lexer lexer(text);
    vector<Token> tokens;

    tokens = lexer.readTokens();

    int l = tokens.size();
    for (int i = 0; i < l; i++) {
        cout << i << tokens[i].toString() << endl;
    }

    Parser parser(tokens);
    /*Clause* sentence1;
    sentence1 = parser.parseClause();
    cout << "£" << endl;
    cout << sentence1->writeTree() << endl;
    delete sentence1; sentence1 = NULL;*/

    cout << "Parsing:" << endl;

    Routine* routine;
    routine = parser.parseRoutine();

    cout << "Writing:" << endl;

    cout << routine->writeTree() << endl;

    delete routine; routine = NULL;

    //Close all files.
    ifs.close();
    ofs.close();
}

/*
Parameters: the input file-stream to be normalised
Return: the string of the file without newlines and with spaces around ',' and '.'.
*/
const string normalise(ifstream& ifs) {
    //Declare local variables.
    string line;
    string text("");
    stringstream ss("");

    ss << ifs.rdbuf();
    text = ss.str();

    //while (getline(ifs, line, '\n')) {
        //cout << "[" << line << "]" << endl;

        /*for (int lastStop = line.find_last_of('.'); lastStop != string::npos; lastStop = line.find_last_of('.', lastStop-1)) {
            //cout << lastStop << endl;

            if ((isdigit(line[lastStop+1]) != 0) && (isdigit(line[lastStop-1]) != 0)) {
                //cout << "Out of bounds: " << line << " " << lastStop << endl;
                continue;
            }

            if ((lastStop != line.length()-1) && (line[lastStop+1] != ' ')) {
                line.insert(lastStop+1, " ");
                lastStop++;
            }
            if ((lastStop != 0) && (line[lastStop-1] != ' '))
                line.insert(lastStop, " ");

            if (lastStop == 0) break;
        }*/

        /*for (int lastComma = line.find_last_of(','); lastComma != string::npos; lastComma = line.find_last_of(',', lastComma-1)) {
            //cout << lastComma << endl;

            if ((isdigit(line[lastComma+1]) != 0) && (isdigit(line[lastComma-1]) != 0)) {
                //cout << "Out of bounds: " << line << " " << lastComma << endl;
                continue;
            }

            if ((lastComma != line.length()-1) && (line[lastComma+1] != ' ')) {
                line.insert(lastComma+1, " ");
                lastComma++;
            }
            if ((lastComma != 0) && (line[lastComma-1] != ' ')) {
                line.insert(lastComma, " ");
                lastComma += 2;
            }

            if (lastComma == 0) break;
        }*/

        /*for (int lastLBracket = line.find_last_of('['); lastLBracket != string::npos; lastLBracket = line.find_last_of('[', lastLBracket-1)) {
            //cout << lastLBracket << endl;

            if ((lastLBracket != line.length()-1) && (line[lastLBracket+1] != ' ') && (isdigit(line[lastLBracket+1]) == 0)) {
                cout << "££0" << endl;
                line.insert(lastLBracket+1, " ");
                lastLBracket++;
            }
            if ((lastLBracket != 0) && (line[lastLBracket-1] != ' ') && (isdigit(line[lastLBracket-1]) == 0)) {
                cout << "££1" << endl;
                line.insert(lastLBracket, " ");
            }

            if (lastLBracket == 0) break;
        }

        for (int lastRBracket = line.find_last_of(']'); lastRBracket != string::npos; lastRBracket = line.find_last_of(']', lastRBracket-1)) {
            //cout << lastRBracket << endl;

            if ((lastRBracket != line.length()-1) && (line[lastRBracket+1] != ' ') && (isdigit(line[lastRBracket+1]) == 0)) {
                line.insert(lastRBracket+1, " ");
                lastRBracket++;
            }
            if ((lastRBracket != 0) && (line[lastRBracket-1] != ' ') && (isdigit(line[lastRBracket-1]) == 0))
                line.insert(lastRBracket, " ");

            if (lastRBracket == 0) break;
        }*/

        //text += line + " ";
    //}

    return text;
}
