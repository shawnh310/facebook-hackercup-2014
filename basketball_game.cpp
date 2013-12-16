#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Player
{
    Player( char* name_,
            int shot_perc_,
            int height_,
            int draft_,
            int play_time_):
        name(name_),
        shot_perc(shot_perc_),
        height(height_),
        draft(draft_),
        play_time(play_time_)
    {
    };
    
    Player()
    {
    };
    
    string name;
    int shot_perc;
    int height;
    int draft;
    int play_time;
};


int draft_cmp( const void* i1, const void* i2 )
{
    Player& p1 = *(Player*)i1;
    Player& p2 = *(Player*)i2;
    
    if ( p1.shot_perc > p2.shot_perc )
        return 1;
    else if ( p1.shot_perc < p2.shot_perc )
        return -1;
    else
    {
        if ( p1.height > p2.height )
            return 1;
        else
            return -1;
    }
}

int bench_cmp( const void* i1, const void* i2 )
{
    Player& p1 = *(Player*)i1;
    Player& p2 = *(Player*)i2;
    
    if ( p1.play_time > p2.play_time )
        return -1;
    else if ( p1.play_time < p2.play_time )
        return 1;
    else
    {
        if ( p1.draft > p2.draft )
            return -1;
        else
            return 1;
    }
}

int court_cmp( const void* i1, const void* i2 )
{
    Player& p1 = *(Player*)i1;
    Player& p2 = *(Player*)i2;
    
    if ( p1.play_time > p2.play_time )
        return 1;
    else if ( p1.play_time < p2.play_time )
        return -1;
    else
    {
        if ( p1.draft > p2.draft )
            return 1;
        else
            return -1;
    }
}


bool name_cmp( string*& name1, string*& name2 )
{
    return lexicographical_compare(name1->begin(), name1->end(), name2->begin(), name2->end());
}

void rotate( vector<Player>& bench, vector<Player>& court )
{
    for ( int i = 0; i < court.size(); i++ )
    {
        court[i].play_time++;
    }
    
    qsort(&(court[0]), court.size(), sizeof(Player), court_cmp);
    Player down = court[court.size()-1];
    court.pop_back();
    
    qsort(&(bench[0]), bench.size(), sizeof(Player), bench_cmp);
    Player up = bench[bench.size()-1];
    bench.pop_back();
    
    court.push_back(up);
    bench.push_back(down);
}


int main(int argc, const char * argv[])
{
    //FILE *fin = fopen("basketball_game_example_input.txt", "r");
    FILE *fin = stdin;
    
    int T;
    fscanf(fin,"%d", &T);
    
    vector<Player> bench1;
    vector<Player> court1;
    
    vector<Player> bench2;
    vector<Player> court2;
    
    for ( int case_id = 1; case_id <= T; case_id++ )
    {
        int N, M, P;
        fscanf(fin,"%d%d%d", &N,&M,&P);
        
        bench1.resize(0);
        court1.resize(0);
        bench2.resize(0);
        court2.resize(0);
        
        vector<Player> players;
        for ( int i = 0; i < N; i++ )
        {
            char name[1024];
            int shot_perc, height;
            fscanf(fin,"%s%d%d", name, &shot_perc, &height);
            
            players.emplace_back(name, shot_perc, height, 0, 0);
        }
        
        qsort(&(players[0]), players.size(), sizeof(Player), draft_cmp);
        
        for ( int i = (int)players.size()-1, draft = 1; i >= 0; i--, draft++)
        {
            players[i].draft = draft;
        }
        
        for ( int i = 0; i < players.size(); i++ )
        {
            if ( players[i].draft % 2 == 1 )
                bench1.push_back(players[i]);
            else
                bench2.push_back(players[i]);
        }
        
        for ( int i = 0; i < P; i++ )
        {
            court1.push_back(bench1[bench1.size()-1]);
            bench1.pop_back();
            
            court2.push_back(bench2[bench2.size()-1]);
            bench2.pop_back();
        }
        
        for ( int i = 0; i < M; i++ )
        {
            if ( bench1.size() > 0 )
                rotate(bench1, court1);
            
            if ( bench2.size() > 0 )
                rotate(bench2, court2);
        }
        
        vector<string*> court_players;
        
        for ( int i = 0; i < court1.size(); i++ )
        {
            court_players.push_back(&(court1[i].name));
        }
        
        for ( int i = 0; i < court2.size(); i++ )
        {
            court_players.push_back(&(court2[i].name));
        }
        
        sort(court_players.begin(), court_players.end(), name_cmp);
        
        printf("Case #%d:", case_id);
        for ( int i = 0; i < court_players.size(); i++ )
        {
            printf(" %s", court_players[i]->c_str());
        }
        printf("\n");
    }
     
     
}

