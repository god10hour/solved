#include <bits/stdc++.h>
using namespace std;

struct Problem {
    int id, order, score;
};
struct Submit {
    int sid, idx;
    int minute;
    char result, pre;
    int score;
};
struct State {
    int c=0;
    int sid=0, before=0, minute=0;
    int pts=0;
    bool solved=0;
};
struct User {
    string name;
    vector<Submit> subs;
    vector<State> prob;
    int submit=0; // sid
    int solved=0; // sid
    int64_t score=0, pen=0;
};

static int64_t days(int y,int m,int d) {
    y-=m<=2;
    int era=(y>=0? y:y-399)/400;
    unsigned yoe=(unsigned)(y-era*400);
    unsigned doy=(153*(m+(m>2? -3:9))+2)/5+d-1;
    unsigned doe=yoe*365+yoe/4-yoe/100+yoe/400+doy;
    return (int64_t)era*146097+(int64_t)doe-719468;
}
static int64_t second(const string& ymd, const string& hms) {
    int y=stoi(ymd.substr(0, 4));
    int m=stoi(ymd.substr(5, 2));
    int d=stoi(ymd.substr(8, 2));
    int H=stoi(hms.substr(0, 2));
    int M=stoi(hms.substr(3, 2));
    int S=stoi(hms.substr(6, 2));
    return 60*(days(y, m, d)*1440+H*60+M)+S;
}
static string str(int64_t minutes, bool format) {
    if (format==0)
        return to_string(minutes);
    int64_t h=minutes/60, m=minutes%60;
    ostringstream oss;
    oss << h << ":" << setw(2) << setfill('0') << m;
    return oss.str();
}

static string token(const State &state, const Problem &prob,
                    int penalty, int last, bool format, bool contest) {
    if (state.c==0) return "0/--";
    bool solved=contest? state.pts>0: state.solved;
    if (!solved) return "w/"+to_string(state.c)+"/--";
    int tries=state.before+1;
    int pen1=state.before*penalty, pen2=state.minute;
    int64_t pen=last? pen2: pen1+pen2;
    string s=str(pen, format);

    if (!contest)
        return "a/"+to_string(tries)+"/"+s;
    char ap=(state.pts==prob.score? 'a':'p');
    return string(1, ap)+"/"+to_string(state.pts)+"/"+to_string(tries)+"/"+s;
}

static int find(const vector<Problem> &probs, int pid) {
    for (int i=0; i<probs.size(); i++)
        if (probs[i].id==pid)
            return i;
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int penalty, last, ce, cscore, format;
    string d, t;
    cin >> penalty;
    cin >> d >> t;
    cin >> last >> ce >> cscore >> format;
    int64_t start=second(d, t);

    int N, M, S;
    cin >> N;
    vector<Problem> probs(N);
    for (int i=0; i<N; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        probs[b-1]={a, b, c};
    }
    if (!cscore) for (auto &p: probs) p.score=0;
    cin >> M;
    vector<string> uid(M);
    vector<User> users(M);
    unordered_map <string, int> uids;
    for (int i=0; i<M; i++)
        cin >> uid[i], uids[uid[i]]=i;
    for (int i=0; i<M; i++) {
        users[i].name=uid[i];
        users[i].prob.assign(N, State{});
    }
    cin >> S;
    for (int i=0; i<S; i++) {
        int sid, pid, result, presult, score;
        string uid, d1, t1;
        cin >> sid >> pid >> uid;
        cin >> result >> presult >> score;
        cin >> d1 >> t1;
        auto it=uids.find(uid);
        if (it==uids.end()) continue;
        if (result==13) continue;
        if (ce==1 && result==11) continue;
        int pidx=find(probs, pid);
        if (pidx<0) continue;

        int u=it->second;
        int64_t sub=second(d1, t1);
        sub-=start;
        if (sub<0) sub=0;
        users[u].subs.push_back(Submit{
            sid, pidx, (int)sub/60,
            (char)result, (char)presult, score
        });
    }

    for (auto &u: users) {
        if (!u.subs.empty())
            sort(u.subs.begin(), u.subs.end(), [](auto a, auto b) {
                     return a.sid<b.sid;
            });
        for (const auto &sb : u.subs) {
            auto &sta=u.prob[sb.idx];
            sta.c++;
            u.submit=max(u.submit, sb.sid);

            if (!cscore) {
                if (sb.result==4 && sb.pre==0) {
                    if (!sta.solved) {
                        sta.solved=1;
                        sta.sid=sb.sid;
                        sta.before=sta.c-1;
                        sta.minute=sb.minute;
                    }
                    u.solved=max(u.solved, sb.sid);
                }
            }
            else {
                int pts=0;
                if (sb.result==4) {
                    if (sb.pre==0 && sb.score==0)
                        pts=probs[sb.idx].score;
                    else  pts=sb.score;
                    if (pts<0) pts=0;
                }
                if (pts>sta.pts) {
                    sta.pts=pts;
                    sta.sid=sb.sid;
                    sta.before=sta.c-1;
                    sta.minute=sb.minute;
                }
                if (pts>0) u.solved=max(u.solved, sb.sid);
            }
        }
    }

    for (auto &u: users) {
        int64_t pen1=0, pen2=0, score=0;
        int c=0, mpen=0;

        for (int i=0; i<N; i++) {
            const auto &sta=u.prob[i];
            bool solved=cscore? sta.pts>0: sta.solved;
            if (!solved) continue;
            pen1+=sta.before*penalty;
            pen2+=sta.minute;
            mpen=max(mpen, sta.minute);
            if (cscore)
                score+=sta.pts;
            else c++;
        }
        u.score=cscore? score:c;
        u.pen=last? pen1+mpen: pen1+pen2;
    }

    vector<int> idx(M); iota(idx.begin(), idx.end(), 0);
    sort(
        idx.begin(), idx.end(), [&](int a, int b) {
            const auto &A=users[a], &B=users[b];
            if (A.score!=B.score) return A.score>B.score;
            if (A.pen!=B.pen) return A.pen<B.pen;
            if (A.solved!=B.solved) return A.solved<B.solved;
            if (A.submit!=B.submit) return A.submit<B.submit;
            return A.name<B.name;
        }
    );

    vector<int> rankof(M);
    int64_t prevS=0, prevP=0, prevR=0;
    for (int i=0; i<M; i++) {
        int u=idx[i];
        if (i==0 || users[u].score!=prevS || users[u].pen!=prevP) {
            prevR=i+1;
            prevS=users[u].score;
            prevP=users[u].pen;
        }
        rankof[u]=prevR;
    }

    for (int i=0; i<M; i++) {
        int u=idx[i];
        auto &user=users[u];
        cout << rankof[u] << ","<< user.name;
        for (int p=0; p<N; p++)
            cout << "," << token(user.prob[p], probs[p], penalty, last, format, cscore);
        cout << "," << user.score << "/" << str(user.pen, format) << '\n';
    }
}