#include <bits/stdc++.h>
using namespace std;

struct Definition {
    bool exact=false;
    int val=0;
    string par, body;
    int calls=0;

    Definition()=default;
    explicit Definition(
        bool exact, int value,
        string param, string body
    ): exact(exact), val(value), par(move(param)), body(move(body)) {}
};

struct Interpreter;
struct Parser {
    const string &s;
    int pos=0;
    Interpreter *it;
    bool has=false;
    string name;
    int val=0;

    explicit Parser(
        const string &s,
        Interpreter *it,
        bool has=false,
        string name="",
        int val=0
    ): s(s), it(it), has(has), name(move(name)), val(val) {}

    int parse_number() {
        int v=0;
        while (pos<s.size() && isdigit(s[pos]))
            v=v*10+(s[pos++]-'0');
        return v;
    }

    string parse_ident() {
        string ide;
        while (pos<s.size() && isalpha(s[pos]))
            ide+=s[pos++];
        return ide;
    }

    int parse_factor();

    int parse_term() {
        int v=parse_factor();
        while (pos<s.size()) {
            char op=s[pos];
            if (op!='*' && op!='/' && op!='%') break;
            pos++;
            int rhs=parse_factor();
            if (op=='*') v*=rhs;
            if (op=='/') v/=rhs;
            if (op=='%') v%=rhs;
        }
        return v;
    }

    int parse_expr() {
        int v=parse_term();
        while (pos<s.size()) {
            char op=s[pos];
            if (op!='+' && op!='-') break;
            pos++;
            int rhs=parse_term();
            if (op=='+') v+=rhs;
            if (op=='-') v-=rhs;
        }
        return v;
    }
};

struct Interpreter {
    unordered_map<string, int> vars;
    unordered_map<string, vector<Definition>> funcs, gfuncs, all;
    vector<string> order;

    static string compact(const string &line) {
        string t;
        for (auto &c: line) if (!isspace(c)) t+=c;
        return t;
    }

    static string ltrim(const string &line) {
        int i=0;
        while (i<line.size() && isspace(line[i])) i++;
        return line.substr(i);
    }

    bool is_command(const string &line, const string &cmd) {
        string t=ltrim(line);
        if (t.size()<cmd.size()) return false;
        if (t.compare(0, cmd.size(), cmd)!=0) return false;
        if (t.size()==cmd.size()) return true;
        return isspace(t[cmd.size()]);
    }

    int eval_expr(
        const string &expr, bool has=false,
        const string &name="", int value=0
    ) {
        Parser p(expr, this, has, name, value);
        return p.parse_expr();
    }

    int call_func(const string &name, int arg) {
        auto &v=funcs[name];
        for (auto &d: v) {
            if (d.val!=arg) continue;
            d.calls++;
            for (auto &e: all[name]) if (e.exact && e.val==arg && e.body==d.body) {
                e.calls++;
                break;
            }
            return eval_expr(d.body, false);
        }
        auto &gv=gfuncs[name];
        for (auto &d: gv) {
            d.calls++;
            for (auto &e: all[name]) if (!e.exact && e.par==d.par && e.body==d.body) {
                e.calls++;
                break;
            }
            return eval_expr(d.body, true, d.par, arg);
        }
        return 0;
    }

    void do_set(const string &line) {
        string t=compact(line);
        int pos=3;
        string name;
        while (pos<t.size() && isalpha(t[pos])) name+=t[pos++];
        pos++;
        string expr=t.substr(pos);
        vars[name]=eval_expr(expr);
    }

    void do_def(const string &line) {
        string t=compact(line), fname, token;
        int pos=3;
        while (pos<t.size() && isalpha(t[pos])) fname+=t[pos++];
        pos++;
        while (t[pos]!=')') token+=t[pos++];
        pos+=2;
        string body=t.substr(pos);
        bool exact=true;
        for (auto &c: token) if (!isdigit(c)) {
            exact=false;
            break;
        }
        if (!funcs.count(fname) && !gfuncs.count(fname)) order.emplace_back(fname);
        if (exact) {
            funcs[fname].emplace_back(true, stoi(token), "", body);
            all[fname].emplace_back(true, stoi(token), "", body);
        } else {
            gfuncs[fname].emplace_back(false, 0, token, body);
            all[fname].emplace_back(false, 0, token, body);
        }
    }

    void do_profile() {
        vector<string> names=order;
        ranges::sort(names);
        for (const auto &name : names) {
            int total=0;
            cout << name << " calls:";
            for (auto &d: all[name]) {
                cout << ' ' << d.calls;
                total+=d.calls;
            }
            cout << " => " << total << '\n';
        }

        for (const auto &name: names) {
            for (auto &d: funcs[name]) d.calls=0;
            for (auto &d: gfuncs[name]) d.calls=0;
            for (auto &d: all[name]) d.calls=0;
        }
    }
};

int Parser::parse_factor() {
    if (isdigit(static_cast<unsigned char>(s[pos]))) return parse_number();
    if (s[pos]=='(') {
        pos++;
        int v=parse_expr();
        pos++;
        return v;
    }
    string id=parse_ident();
    if (pos<s.size() && s[pos]=='(') {
        pos++;
        int arg=parse_expr();
        pos++;
        return it->call_func(id, arg);
    }
    if (has && id==name) return val;
    return it->vars[id];
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    Interpreter it;
    string line;
    while (getline(cin, line)) {
        string trimmed=Interpreter::ltrim(line);
        if (trimmed=="exit") break;
        if (trimmed=="profile") {
            it.do_profile();
            continue;
        }
        if (it.is_command(line, "set")) {
            it.do_set(line);
            continue;
        }
        if (it.is_command(line, "def")) {
            it.do_def(line);
            continue;
        }
        string expr=Interpreter::compact(line);
        cout << ">> " << it.eval_expr(expr) << '\n';
    }
}