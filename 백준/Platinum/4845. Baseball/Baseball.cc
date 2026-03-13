#include <bits/stdc++.h>
using namespace std;

struct Team {
    string team;
    array<string, 9> name;
    array<double, 9> hit, sac;
    int curr, runs=0, hits=0;
};
Team home, visitor;

int seed;
int u_rand() {
    seed=(seed*25173+13849)%65536;
    return seed;
}

void read_team(Team *team) {
    cin >> team->team;
    for (int i=0; i<9; i++)
        cin >> team->name[i] >> team->hit[i] >> team->sac[i];
    team->curr=team->hits=team->runs=0;
}
void print_pair(const string &a, const string &b) {
    cout << setw(17) << a << ' ' << setw(15) << b << '\n';
}

void run_half(
    Team *team, int *runs, int *hits,
    int *nruns, int *nhits, int offset
) {
    array base{-1, -1, -1, -1, -1};
    int out=0;
    auto success=[&](double rat) {
        double r=u_rand()/65536.0;
        return r<=rat;
    };

    while (out<3) {
        if ((base[2]>=0 && out==0) || (base[3]>=0 && out<2)) {
            if (success(team->sac[team->curr])) {
                for (int i=4; i>1; i--) base[i]=base[i-1];
                base[1]=-1;
            }
            out++;
        } else {
            if (success(team->hit[team->curr])) {
                for (int i=4; i>1; i--) base[i]=base[i-1];
                base[1]=team->curr+offset;
                hits[(*nhits)++]=team->curr+offset;
                team->hits++;
            } else out++;
        }
        if (++team->curr==9) team->curr=0;
        if (out<3 && base[4]>=0) {
            runs[(*nruns)++]=base[4];
            base[4]=-1;
            team->runs++;
        }
    }
}

void run_inning(int inn) {
    int runs[1000], hits[1000];
    int nruns=0, nhits=0;
    cout << "Inning " << inn << ":\n";
    run_half(&visitor, runs, hits, &nruns, &nhits, 0);
    if (inn!=9 || visitor.runs>=home.runs)
        run_half(&home, runs, hits, &nruns, &nhits, 100);

    cout << "Hits:\n";
    if (nhits>0) {
        for (int i=0; i<nhits; i++) {
            if (hits[i]<100)
                print_pair(visitor.name[hits[i]], visitor.team);
            else {
                hits[i]-=100;
                print_pair(home.name[hits[i]], home.team);
            }
        }
    } else cout << "  none\n";
    cout << "\nRuns:\n";
    if (nruns>0) {
        for (int i=0; i<nruns; i++) {
            if (runs[i]<100)
                print_pair(visitor.name[runs[i]], visitor.team);
            else {
                runs[i]-=100;
                print_pair(home.name[runs[i]], home.team);
            }
        }
    } else cout << "  none\n";
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, inn;
    cin >> n;
    for (int i=1; i<=n; i++) {
        seed=1;
        read_team(&visitor);
        read_team(&home);

        if (i>1) cout << string(60, '=') << '\n';
        cout << "Game " << i << ": " << visitor.team
             << " vs. " << home.team << "\n\n";
        for (inn=1; inn<=9; inn++) run_inning(inn);
        while (visitor.runs==home.runs) run_inning(inn++);
        cout << "End of Game:\n";
        cout << setw(17) << visitor.team << ' '
             << visitor.runs << " runs, " << visitor.hits << " hits\n";
        cout << setw(17) << home.team << ' '
             << home.runs << " runs, " << home.hits << " hits\n";
    }
}