
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stdexcept>
#include <cctype>
#include <limits>
#include <algorithm>

using namespace std;

// ============================================================
// 1. INPUT HELPERS
// ============================================================

int getChoice(int minimum, int maximum)
{
    int choice;

    while (true)
    {
        cout << "Enter your choice: ";

        if (cin >> choice && choice >= minimum && choice <= maximum)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }

        cout << "Invalid choice. Enter a number from "
             << minimum << " to " << maximum << ".\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int getBit(const string &prompt)
{
    int bit;

    while (true)
    {
        cout << prompt;

        if (cin >> bit && (bit == 0 || bit == 1))
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return bit;
        }

        cout << "Invalid input. Enter 0 or 1.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string getLine(const string &prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

// ============================================================
// 2. BASIC LOGIC GATES
// ============================================================

bool applyGate(const string &gate, bool a, bool b = false)
{
    if (gate == "AND")
        return a && b;
    if (gate == "OR")
        return a || b;
    if (gate == "NOT")
        return !a;
    if (gate == "XOR")
        return a != b;
    if (gate == "NAND")
        return !(a && b);
    if (gate == "NOR")
        return !(a || b);
    if (gate == "XNOR")
        return a == b;

    throw runtime_error("Unknown logic gate.");
}

void simulateSingleGate()
{
    cout << "\n--- SINGLE LOGIC GATE ---\n";
    cout << "1. AND\n";
    cout << "2. OR\n";
    cout << "3. NOT\n";
    cout << "4. XOR\n";
    cout << "5. NAND\n";
    cout << "6. NOR\n";
    cout << "7. XNOR\n";

    int choice = getChoice(1, 7);

    const string gates[] = {
        "AND", "OR", "NOT", "XOR", "NAND", "NOR", "XNOR"};

    string gate = gates[choice - 1];

    int a = getBit("Enter input A (0 or 1): ");
    int b = 0;

    if (gate != "NOT")
    {
        b = getBit("Enter input B (0 or 1): ");
    }

    bool result = applyGate(gate, a, b);

    cout << "\nGate: " << gate << '\n';
    cout << "Input A: " << a << '\n';

    if (gate != "NOT")
    {
        cout << "Input B: " << b << '\n';
    }

    cout << "Output: " << result << "\n\n";
}

void generateGateTruthTable()
{
    cout << "\n--- GATE TRUTH TABLE ---\n";
    cout << "1. AND\n";
    cout << "2. OR\n";
    cout << "3. NOT\n";
    cout << "4. XOR\n";
    cout << "5. NAND\n";
    cout << "6. NOR\n";
    cout << "7. XNOR\n";

    int choice = getChoice(1, 7);

    const string gates[] = {
        "AND", "OR", "NOT", "XOR", "NAND", "NOR", "XNOR"};

    string gate = gates[choice - 1];

    cout << "\nTruth table for " << gate << ":\n";

    if (gate == "NOT")
    {
        cout << "A | Output\n";
        cout << "----------\n";

        for (int a = 0; a <= 1; ++a)
        {
            cout << a << " |   "
                 << applyGate(gate, a) << '\n';
        }
    }
    else
    {
        cout << "A B | Output\n";
        cout << "------------\n";

        for (int a = 0; a <= 1; ++a)
        {
            for (int b = 0; b <= 1; ++b)
            {
                cout << a << " " << b << " |   "
                     << applyGate(gate, a, b) << '\n';
            }
        }
    }

    cout << '\n';
}

// ============================================================
// 3. BOOLEAN EXPRESSION TOKENIZER
// ============================================================

enum class TokenType
{
    VARIABLE,
    AND,
    OR,
    NOT,
    XOR,
    NAND,
    NOR,
    XNOR,
    LEFT_PAREN,
    RIGHT_PAREN,
    END
};

struct Token
{
    TokenType type;
    string text;
};

string toUpperCase(string text)
{
    for (char &c : text)
    {
        c = static_cast<char>(
            toupper(static_cast<unsigned char>(c)));
    }
    return text;
}

vector<Token> tokenize(const string &expression)
{
    vector<Token> tokens;
    size_t i = 0;

    while (i < expression.size())
    {
        unsigned char c =
            static_cast<unsigned char>(expression[i]);

        if (isspace(c))
        {
            ++i;
            continue;
        }

        if (expression[i] == '(')
        {
            tokens.push_back({TokenType::LEFT_PAREN, "("});
            ++i;
            continue;
        }

        if (expression[i] == ')')
        {
            tokens.push_back({TokenType::RIGHT_PAREN, ")"});
            ++i;
            continue;
        }

        if (isalpha(c) || expression[i] == '_')
        {
            size_t start = i;

            while (i < expression.size())
            {
                unsigned char current =
                    static_cast<unsigned char>(expression[i]);

                if (isalnum(current) || expression[i] == '_')
                {
                    ++i;
                }
                else
                {
                    break;
                }
            }

            string word = expression.substr(start, i - start);
            string upper = toUpperCase(word);

            if (upper == "AND")
            {
                tokens.push_back({TokenType::AND, upper});
            }
            else if (upper == "OR")
            {
                tokens.push_back({TokenType::OR, upper});
            }
            else if (upper == "NOT")
            {
                tokens.push_back({TokenType::NOT, upper});
            }
            else if (upper == "XOR")
            {
                tokens.push_back({TokenType::XOR, upper});
            }
            else if (upper == "NAND")
            {
                tokens.push_back({TokenType::NAND, upper});
            }
            else if (upper == "NOR")
            {
                tokens.push_back({TokenType::NOR, upper});
            }
            else if (upper == "XNOR")
            {
                tokens.push_back({TokenType::XNOR, upper});
            }
            else
            {
                tokens.push_back({TokenType::VARIABLE, word});
            }

            continue;
        }

        throw runtime_error(
            string("Unexpected character: ") + expression[i]);
    }

    tokens.push_back({TokenType::END, ""});
    return tokens;
}

// ============================================================
// 4. BOOLEAN EXPRESSION PARSER
//
// Precedence, from highest to lowest:
// Parentheses > NOT > AND/NAND > XOR/XNOR > OR/NOR
// ============================================================

class Parser
{
private:
    vector<Token> tokens;
    size_t position;
    map<string, bool> values;

    Token current() const
    {
        return tokens[position];
    }

    bool match(TokenType type)
    {
        if (current().type == type)
        {
            ++position;
            return true;
        }
        return false;
    }

    bool parseOr()
    {
        bool result = parseXor();

        while (current().type == TokenType::OR ||
               current().type == TokenType::NOR)
        {
            TokenType op = current().type;
            ++position;

            bool right = parseXor();

            if (op == TokenType::OR)
            {
                result = result || right;
            }
            else
            {
                result = !(result || right);
            }
        }

        return result;
    }

    bool parseXor()
    {
        bool result = parseAnd();

        while (current().type == TokenType::XOR ||
               current().type == TokenType::XNOR)
        {
            TokenType op = current().type;
            ++position;

            bool right = parseAnd();

            if (op == TokenType::XOR)
            {
                result = result != right;
            }
            else
            {
                result = result == right;
            }
        }

        return result;
    }

    bool parseAnd()
    {
        bool result = parseUnary();

        while (current().type == TokenType::AND ||
               current().type == TokenType::NAND)
        {
            TokenType op = current().type;
            ++position;

            bool right = parseUnary();

            if (op == TokenType::AND)
            {
                result = result && right;
            }
            else
            {
                result = !(result && right);
            }
        }

        return result;
    }

    bool parseUnary()
    {
        if (match(TokenType::NOT))
        {
            return !parseUnary();
        }

        return parsePrimary();
    }

    bool parsePrimary()
    {
        if (current().type == TokenType::VARIABLE)
        {
            string name = current().text;
            ++position;

            auto it = values.find(name);

            if (it == values.end())
            {
                throw runtime_error(
                    "No input value supplied for variable: " + name);
            }

            return it->second;
        }

        if (match(TokenType::LEFT_PAREN))
        {
            bool result = parseOr();

            if (!match(TokenType::RIGHT_PAREN))
            {
                throw runtime_error("Missing closing parenthesis.");
            }

            return result;
        }

        throw runtime_error(
            "Expected a variable or an opening parenthesis.");
    }

public:
    Parser(const vector<Token> &inputTokens,
           const map<string, bool> &inputValues)
        : tokens(inputTokens), position(0), values(inputValues) {}

    bool evaluate()
    {
        bool result = parseOr();

        if (current().type != TokenType::END)
        {
            throw runtime_error(
                "Unexpected extra token: " + current().text);
        }

        return result;
    }
};

bool evaluateExpression(
    const vector<Token> &tokens,
    const map<string, bool> &values)
{
    Parser parser(tokens, values);
    return parser.evaluate();
}

set<string> findVariables(const vector<Token> &tokens)
{
    set<string> variables;

    for (const Token &token : tokens)
    {
        if (token.type == TokenType::VARIABLE)
        {
            variables.insert(token.text);
        }
    }

    return variables;
}

// ============================================================
// 5. EXPRESSION SIMULATOR
// ============================================================

void evaluateOneExpression()
{
    cout << "\n--- BOOLEAN EXPRESSION EVALUATOR ---\n";
    cout << "Example: (A AND B) OR NOT C\n";
    cout << "Operators: AND, OR, NOT, XOR, NAND, NOR, XNOR\n\n";

    string expression = getLine("Enter expression: ");

    vector<Token> tokens = tokenize(expression);
    set<string> variableSet = findVariables(tokens);

    if (variableSet.empty())
    {
        throw runtime_error(
            "Expression must contain at least one variable.");
    }

    map<string, bool> values;

    for (const string &variable : variableSet)
    {
        values[variable] =
            getBit("Enter value for " + variable + " (0 or 1): ");
    }

    bool result = evaluateExpression(tokens, values);

    cout << "\nExpression: " << expression << '\n';
    cout << "Output: " << result << "\n\n";
}

void generateExpressionTruthTable()
{
    cout << "\n--- EXPRESSION TRUTH TABLE ---\n";
    cout << "Example: (A AND B) OR NOT C\n\n";

    string expression = getLine("Enter expression: ");

    vector<Token> tokens = tokenize(expression);
    set<string> variableSet = findVariables(tokens);
    vector<string> variables(
        variableSet.begin(), variableSet.end());

    if (variables.empty())
    {
        throw runtime_error(
            "Expression must contain at least one variable.");
    }

    if (variables.size() > 10)
    {
        throw runtime_error(
            "Maximum supported variables: 10.");
    }

    cout << "\nTruth table for: " << expression << "\n\n";

    for (const string &variable : variables)
    {
        cout << variable << " ";
    }
    cout << "| Output\n";

    for (size_t i = 0; i < variables.size() * 2 + 10; ++i)
    {
        cout << "-";
    }
    cout << '\n';

    size_t rows = size_t{1} << variables.size();

    for (size_t row = 0; row < rows; ++row)
    {
        map<string, bool> values;

        for (size_t col = 0; col < variables.size(); ++col)
        {
            size_t shift = variables.size() - 1 - col;
            bool bit = (row >> shift) & 1U;

            values[variables[col]] = bit;
            cout << bit << " ";
        }

        bool output = evaluateExpression(tokens, values);
        cout << "|   " << output << '\n';
    }

    cout << '\n';
}

// ============================================================
// 6. HALF-ADDER CIRCUIT
// ============================================================

void simulateHalfAdder()
{
    cout << "\n--- HALF-ADDER SIMULATOR ---\n";
    cout << "A half-adder adds two single binary digits.\n\n";

    int a = getBit("Enter input A (0 or 1): ");
    int b = getBit("Enter input B (0 or 1): ");

    bool sum = applyGate("XOR", a, b);
    bool carry = applyGate("AND", a, b);

    cout << "\nInputs: A = " << a << ", B = " << b << '\n';
    cout << "Sum:    " << sum << "  (A XOR B)\n";
    cout << "Carry:  " << carry << "  (A AND B)\n\n";
}

// ============================================================
// 7. MAIN MENU
// ============================================================

void showMenu()
{
    cout << "========================================\n";
    cout << "       DIGITAL LOGIC WORKBENCH\n";
    cout << "========================================\n";
    cout << "1. Simulate a single logic gate\n";
    cout << "2. Generate a gate truth table\n";
    cout << "3. Evaluate a Boolean expression\n";
    cout << "4. Generate an expression truth table\n";
    cout << "5. Simulate a half-adder circuit\n";
    cout << "0. Exit\n";
    cout << "========================================\n";
}

int main()
{
    bool running = true;

    cout << "\nWelcome to Thomas Jin's Digital Logic Workbench!\n";

    while (running)
    {
        showMenu();
        int choice = getChoice(0, 5);

        try
        {
            switch (choice)
            {
            case 1:
                simulateSingleGate();
                break;

            case 2:
                generateGateTruthTable();
                break;

            case 3:
                evaluateOneExpression();
                break;

            case 4:
                generateExpressionTruthTable();
                break;

            case 5:
                simulateHalfAdder();
                break;

            case 0:
                running = false;
                cout << "\nThank you for using "
                     << "Thomas Jin's Digital Logic Workbench!\n";
                break;
            }
        }
        catch (const exception &error)
        {
            cout << "\nError: " << error.what() << "\n\n";
        }
    }

    return 0;
}