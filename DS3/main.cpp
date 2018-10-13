

#include <iostream>
#include <algorithm>
#include <regex>

#define MENU_CHECK      1
#define MENU_TOPOSTFIX  2
#define MENU_SOLVE      3
#define MENU_QUIT       4

#define ASCII_SIZE 256

//#define DEBUGGING


using namespace std;

enum Type {

    PARENTHESES_L,
    PARENTHESES_R,
    OPERATOR,
    NUMBER,
    SPACE,
    UNDEFINE,
    INIT

};

class Data {

public:
    union Value {
        char c;
        int i32;
    };

    Value value;
    Type type;

    Data() 
    {
    }

    Data(Type t, int v1) 
    {
        value.i32 = v1;
        type = t;
    }

    Data(Type t, char v1) 
    {
        value.c = v1;
        type = t;
    }

};

int priority[ASCII_SIZE];
vector<pair<regex, Type>> tokenDefine;

class LinkedList {
private:

    typedef struct node {
        Data data;
        node *next, *prev;
    } node;

    node *firstNode, *endNode;

public:

    LinkedList()
    {
        firstNode = endNode = nullptr;
    }

    void pop_back() 
    {
        // mark remove node
        node *rmNode = endNode;

        if (rmNode == nullptr) {  // nothing
            throw "LinkedList empty!!";

        } else if (firstNode == endNode) {           // only one node
            endNode = firstNode = nullptr;

        } else {                             // not only one
            // replace end node with prev
            endNode = rmNode->prev;
            // unlink
            endNode->next = nullptr;
        }

        // free memory
        delete rmNode;
        rmNode = nullptr;
    }

    void push_back(const Data d) 
    {
        node *newNode = new node;
        newNode->data = d;
        newNode->next  = nullptr;

        if (firstNode == nullptr) {  // no node
            firstNode = endNode = newNode;
            newNode->prev = nullptr;

        } else {              // have node
            // set new node prev
            newNode->prev = endNode;                        
            // set prev node link to newNode
            endNode->next = newNode;                        
            // ptr to new
            endNode = newNode;
        }
    }  
   
    int size()
    {
        int count = 0;
        node *cur = firstNode;   // current 

        while (cur != nullptr)
            cur = cur->next, count++;

        return count;
    }

    bool empty()
    {
        return firstNode == nullptr;
    }
    
    Data back()
    {
        return endNode->data;
    }

    void print()
    {
        // current
        node *cur = firstNode;

        while (cur != nullptr) {
            if (cur->data.type == NUMBER)
                cout << cur->data.value.i32;
            else 
                cout << cur->data.value.c;

            cout << (cur != endNode ? ',' : '\n');
            cur = cur->next;
        }

        cout.flush();
    }

    void clear()
    {
        node *cur = firstNode;   // current 
        firstNode = nullptr;
        while (cur != nullptr) {
            if (cur->prev != nullptr)
                delete cur->prev;

            cur = cur->next;
        }
    }
    
    // range based for
    class iterator {
        node *current;

    public: 
        iterator(node *node) 
        {
            current = node;
        }

        Data operator*()
        {
            return current->data;
        }

        bool operator!=(const iterator &it2)
        {
            return current != it2.current;
        }

        iterator &operator++()
        {
            current = current->next;
            return *this;
        }
    };

    iterator begin()
    {
        return iterator(firstNode);
    }

    iterator end()
    {
        return iterator(nullptr);
    }

};

class Stack {
    LinkedList stackList;


public:

    int size() 
    {
        return stackList.size();
    }

    bool empty()
    {
        return stackList.empty();
    }

    Data top()
    {
        return stackList.back(); 
    }
    
    void pop()
    {   
        #ifdef DEBUGGING
            cout << "pop:" << top().type<< " "<< (top().type == NUMBER ? top().value.i32 : top().value.c) << endl; 
        #endif

        stackList.pop_back();
    }

    void push(Data c)
    {
        #ifdef DEBUGGING
            cout << "push:" << c.type<< " " << (c.type == NUMBER ? c.value.i32 : c.value.c) << endl; 
        #endif

        stackList.push_back(c);
    }
    
    void print() 
    {
        stackList.print();
    }

};

void errorHandling(string message)
{
    if (cin.eof())
        exit(0);

    // 恢復cin的狀態 
    cin.clear();

    // 消滅最多2048個字元遇到\n 
    cin.ignore(2048, '\n');

    // 顯示錯誤訊息
    cout << message << endl;
}

class Tokenizer {
    string str;
    Data ret;

public:  
    Tokenizer(string strGet) 
    {
        ret.type = INIT; 
        str = string(strGet);
    }

    bool hasNext() 
    {
        return !str.empty() && ret.type != UNDEFINE;
    }

    bool hasDefine() 
    {
        return ret.type != UNDEFINE;
    }

    Data nextToken();

};

Data Tokenizer::nextToken()
{
    smatch m;
    
    for (auto rgx = tokenDefine.begin(); rgx != tokenDefine.end(); ++rgx) {
        if (!regex_search(str, m, rgx->first)) 
            continue;

        string get = m.str();
        str = m.suffix().str();

        if (rgx->second == NUMBER)
            return ret = Data(rgx->second, stoi(get));

        else 
            return ret = Data(rgx->second, get[0]);
    }   

    throw "\t" + str + "\n" +
          "\t^ is not a legitimate character." + "\n";

    return Data(UNDEFINE, ' ');
}

void syntaxNumber(Stack &stack, Data &tmp)
{
    if (stack.empty()) {
        stack.push(tmp);
        return;
    }

    if (stack.top().type == NUMBER)
        throw "Error 3: there is one extra operand.";
    else if (stack.top().type == OPERATOR)
        stack.pop();

    stack.push(tmp);
}

void syntaxParenthesesR(Stack &stack)
{
    while (!stack.empty()) {
        if (stack.top().type == PARENTHESES_L) {
            stack.pop(); 
            stack.push(Data(NUMBER, ' '));
            return;
        } 

        stack.pop(); 
    }

    if (stack.empty()) 
        throw "Error 2: there is one extra close parenthesis.";
}

void syntaxOperator(Stack &stack, Data &tmp)
{
    if (stack.empty()) 
        throw "Error 3: there is one extra operator.";

    if (stack.top().type == NUMBER) {
        stack.pop();
        stack.push(tmp);
    }
}

void syntaxCheck(string str)
{
    Stack stack;
    Tokenizer tokenizer(str);
    Data tmp;
    while (tokenizer.hasNext()) {
        tmp = tokenizer.nextToken();    
        if (!tokenizer.hasDefine()) 
            return;

        switch(tmp.type) {
        case NUMBER:
            syntaxNumber(stack, tmp);
            break;

        case PARENTHESES_R:
            syntaxParenthesesR(stack); 
            break;

        case PARENTHESES_L:
            syntaxNumber(stack, tmp);
            break;

        case OPERATOR:
            syntaxOperator(stack, tmp);
            break;
        }
    }

    if (!stack.empty()) {
        while (stack.size() > 1)
            stack.pop();

        if (stack.top().type == PARENTHESES_L) {
            throw "Error 2: there is one extra open parenthesis.";
        }
        // if (stack.top().type != NUMBER || stack.size() != 1)
        //    throw "error4" ;
    }


}

void calculate(int &a, int &b, char oper)
{
    switch (oper) {
    case '+':
        a += b;
        break;

    case '-':
        a -= b;
        break;

    case '*':
        a *= b;
        break;

    case '/':
        if (b == 0) // a/0
            throw "num / 0 !!!";
        else
            a /= b;
    }
}

int task3(LinkedList postfix)
{
    Stack stack;
    for (Data data : postfix) {
        if (data.type == NUMBER)
            stack.push(data);

        else if (data.type == OPERATOR) {
            int a, b;
            char oper = data.value.c;  
            
            // get two number
            b = stack.top().value.i32;
            stack.pop();
            a = stack.top().value.i32;
            stack.pop();

            calculate(a, b, oper);
            stack.push(Data(NUMBER, a));
        }
    }

    cout << "Answer: " << stack.top().value.i32 << endl;
    return 0;
}

void toPostParenthesesR(Stack &stack, LinkedList &postfix)
{
    while (!stack.empty()) {
        if (stack.top().type == PARENTHESES_L)
            break;

        postfix.push_back(stack.top());
        stack.pop();
    }

    if (!stack.empty())
        stack.pop();
}

void toPostOperator(Stack &stack, Data &tmp, LinkedList &postfix)
{
    if (stack.empty()) {
        stack.push(tmp);
        return;
    }

    Data top = stack.top();
    if (top.type != OPERATOR) {
        stack.push(tmp);
        return;
    }  
    
    // 
    while (priority[tmp.value.c] >= priority[top.value.c] && top.type == OPERATOR) {

        postfix.push_back(top);
        stack.pop();

        if (stack.empty()) {
            stack.push(tmp);
            return;
        }

        top = stack.top();
    } 

    stack.push(tmp);
}

int task2(string str)
{
    Stack stack;
    LinkedList postfix;
    Tokenizer tokenizer(str);
    Data tmp;
    while (tokenizer.hasNext()) {
        tmp = tokenizer.nextToken();     
        switch(tmp.type) {
        case NUMBER:
            postfix.push_back(tmp);
            break;

        case PARENTHESES_R:
            toPostParenthesesR(stack, postfix);
            break;

        case PARENTHESES_L:
            stack.push(tmp);
            break;

        case OPERATOR:
            toPostOperator(stack, tmp, postfix);
            break;
        }
    }

    // dump
    while (!stack.empty()) {
        Data top = stack.top();
        stack.pop();
        postfix.push_back(top);
    }
    
    // print
    cout << "Postfix expression: ";
    postfix.print();

    // next task
    task3(postfix);
    postfix.clear();
    return 0;
}


int task1()
{
    string expr;

    // input
    cout << "Input:";
    cin.ignore(2048, '\n');
    getline(cin, expr);

    #ifdef DEBUGGING
        cout << "expr: " <<expr << endl;
    # endif

    try {
        // check syntax
        //
        syntaxCheck(expr);
        cout << "It is a legitimate infix expression." << endl;

        task2(expr);

    } catch (invalid_argument &e) {
        cout << e.what();
    } catch (exception &e) {
        cout << e.what();   
    
    } catch (char const *e) {
        cout << e << endl;

    } catch (string &e) {
        cout << e << endl;

    }
    
    return 0;
}

void init()
{
    // disable priority
    fill(&priority[0], &priority[ASCII_SIZE], -1);
    
    priority['('] = 5;
    priority[')'] = 5;
    priority['*'] = 10;
    priority['/'] = 10;
    priority['+'] = 20;
    priority['-'] = 20;

    // num   
    // oper  [+\-*/]
    tokenDefine = vector<pair<regex, Type>> {
        { regex("^ +"), SPACE },
        { regex("^[0-9]+"), NUMBER },
        { regex("^[+\\-*/]"), OPERATOR },
        { regex("^\\)"), PARENTHESES_R },
        { regex("^\\("), PARENTHESES_L }
    };
}


int main(int argc, char *argv[])
{
    int mode;                           // 選單選項
    int result;                         // 指令回傳檢查
    init();
     
    while (true) {

        // 輸出選單
        cout << "              MENU              " << endl;
        cout << "* 1.       Calculator          *" << endl;
        cout << "* 4.          Quit             *" << endl;
        cout << "choice: ";

        // 輸入選擇
        cin >> mode;
        if (cin.eof())
            return 0;

        // 判斷選擇的內容
        switch (mode) {
        case MENU_QUIT:
            return 0;               // 退出

        case MENU_CHECK:
            task1();
            break;

        default:
            errorHandling("Error: Command not found!");
            continue;
        }

        // 檢查回傳值是否為successful
        if (!result)
            return 1;
        else cout << endl;
    }

    return 0;
}

