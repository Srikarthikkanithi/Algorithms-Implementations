#include <bits/stdc++.h>
using namespace std;
typedef long long int lwi;
class Toposort;
class GraphAlgorithm;
class isCycle;
class indepComponent;
class validOrder;
class maxHype;
// comparator class where i pass a vector of indices and convert the vector in a topological order
class Toposort
{
public:
    bool operator()(pair<lwi, lwi> &p1, pair<lwi, lwi> &p2)
    {
        // func where i sort the passed vector in topological order of vertices
        if (p1.second != p2.second)
        {
            return p1.second > p2.second;
        }
        return p1.first < p2.first;
    }
};
class paircomparator
{
public:
    bool operator()(pair<lwi, lwi> &p1, pair<lwi, lwi> &p2)
    {
        if (p1.second != p2.second)
        {
            return p1.second < p2.second;
        }
        return p1.first > p2.first;
    }
};
class GraphAlgorithm
{
public:
    virtual void Query(vector<lwi> &v1, vector<vector<lwi>> &m1) = 0; // virtual func to override in child class
};
class isCycle : public GraphAlgorithm
{
public:
    void Query(vector<lwi> &v1, vector<vector<lwi>> &m1)
    {
        // func overriding for checking cycle in a directed graph
        lwi len_v1 = v1.size();
        vector<lwi> travelled(len_v1, 2);
        bool ch = true;
        for (lwi i = 1; i < len_v1; i++)
        {
            if (travelled[i] == 2)
            {
                travelled[i] = 1;
                dfs_visit(travelled, i, ch, m1);
            }
            if(!ch){
                break;
            }
        }
        if (!ch)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
    void dfs_visit(vector<lwi> &travelled1, lwi ind, bool &ch, vector<vector<lwi>> &m1)
    {
        if(!ch){
            travelled1[ind]=0;
            return;
        }
        lwi adj_len = m1[ind].size();
        for (lwi i = 0; i < adj_len; i++)
        {
            if (travelled1[m1[ind][i]] == 2)
            {
                travelled1[m1[ind][i]] = 1;
                dfs_visit(travelled1, m1[ind][i], ch, m1);
            }
            else if (travelled1[m1[ind][i]] == 1)
            {
                travelled1[ind]=0;
                ch = false;
                return;
            }
            if(!ch) break;
        }
        travelled1[ind] = 0;
    }
};
class indepComponent : public GraphAlgorithm
{
public:
    void Query(vector<lwi> &v1, vector<vector<lwi>> &m1)
    {
        // func overriding for counting the no of scc
        lwi len_v1 = v1.size(), t = 0;
        vector<lwi> travelled(len_v1, 2), ftimes(len_v1, 0);
        for (lwi i = 1; i < len_v1; i++)
        {
            if (travelled[i] == 2)
            {
                travelled[i] = 1;
                dfs_visit(travelled, i, m1, t, ftimes);
            }
        }
        vector<pair<lwi, lwi>> vert_ftime;
        for (lwi i = 1; i < len_v1; i++)
        {
            vert_ftime.push_back({i, ftimes[i]});
        }
        sort(vert_ftime.begin(), vert_ftime.end(), Toposort());
        vector<lwi> modified_vert_seq(len_v1, 0);
        for (lwi i = 1; i < len_v1; i++)
        {
            modified_vert_seq[i] = vert_ftime[i - 1].first;
        }
        vector<vector<lwi>> adj_list_gt(len_v1);
        for (lwi i = 1; i < len_v1; i++)
        {
            lwi adj_len = m1[i].size();
            for (lwi j = 0; j < adj_len; j++)
            {
                adj_list_gt[m1[i][j]].push_back(i);
            }
        }
        lwi max_vertices = 0, no_of_vertices = 0, no_of_scc = 0;
        vector<lwi> travelled2(len_v1, 2);
        for (lwi i = 1; i < len_v1; i++)
        {
            lwi ind = modified_vert_seq[i];
            if (travelled2[ind] == 2)
            {
                travelled2[ind] = 1;
                no_of_scc++;
                no_of_vertices = 1;
                dfs_visit2(travelled2, ind, adj_list_gt, no_of_vertices);
                max_vertices = max(max_vertices, no_of_vertices);
            }
        }
        cout << no_of_scc << " " << max_vertices << endl;
    }
    void dfs_visit(vector<lwi> &travelled1, lwi ind, vector<vector<lwi>> &m1, lwi &time, vector<lwi> &ftimes1)
    {
        time++;
        travelled1[ind] = 1;
        lwi adj_len = m1[ind].size();
        for (lwi i = 0; i < adj_len; i++)
        {
            if (travelled1[m1[ind][i]] == 2)
            {
                travelled1[m1[ind][i]]=1;
                dfs_visit(travelled1, m1[ind][i], m1, time, ftimes1);
            }
        }
        time++;
        ftimes1[ind] = time;
        travelled1[ind] = 0;
    }
    void dfs_visit2(vector<lwi> &travelled, lwi ind, vector<vector<lwi>> &m1, lwi &no_of_vertices)
    {
        lwi adj_len = m1[ind].size();
        for (lwi i = 0; i < adj_len; i++)
        {
            if (travelled[m1[ind][i]] == 2)
            {
                travelled[m1[ind][i]]=1;
                no_of_vertices++;
                dfs_visit2(travelled, m1[ind][i], m1, no_of_vertices);
            }
        }
        travelled[ind] = 0;
    }
};
class validOrder : public GraphAlgorithm
{
public:
    void Query(vector<lwi> &v1, vector<vector<lwi>> &m1)
    {
        lwi len_v1 = v1.size(), t = 0;
        vector<lwi> travelled(len_v1, 2), ftimes(len_v1, 0);
        bool ch = true;
        for (lwi i = 1; i < len_v1; i++)
        {
            if (travelled[i] == 2)
            {
                travelled[i] = 1;
                dfs_visit(travelled, i, ch, m1, t, ftimes);
            }
            if(!ch){
                break;
            }
        }
        vector<vector<lwi>> adj_list_gt(len_v1);
        for (lwi i = 1; i < len_v1; i++)
        {
            lwi adj_len = m1[i].size();
            for (lwi j = 0; j < adj_len; j++)
            {
                adj_list_gt[m1[i][j]].push_back(i);
            }
        }
        vector<lwi> indeg(len_v1, 0);
        for (lwi i = 1; i < len_v1; i++)
        {
            lwi p = adj_list_gt[i].size();
            indeg[i] = p;
        }
        if (ch)
        {
            priority_queue<lwi, vector<lwi>, greater<lwi>> pq;
            vector<bool> travelled1(len_v1, 0);
            for (lwi i = 1; i < len_v1; i++)
            {
                if (indeg[i] == 0)
                {
                    pq.push(i);
                }
            }
            while (!pq.empty())
            {
                lwi present_node = pq.top();
                pq.pop();
                if (travelled1[present_node] == 0)
                {
                    cout << present_node << " ";
                    lwi adj_len = m1[present_node].size();
                    for (lwi i = 0; i < adj_len; i++)
                    {
                        lwi v = m1[present_node][i];
                        if (travelled1[v] == 0)
                        {
                            indeg[v]--;
                            if (indeg[v] == 0)
                            {
                                pq.push(v);
                            }
                        }
                    }
                    travelled1[present_node] = 1;
                }
            }
            cout << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
    void dfs_visit(vector<lwi> &travelled1, lwi ind, bool &ch, vector<vector<lwi>> &m1, lwi &time, vector<lwi> &ftimes1)
    {
        if(!ch){
            travelled1[ind]=0;
            return;
        }
        lwi adj_len = m1[ind].size();
        time++;
        for (lwi i = 0; i < adj_len; i++)
        {
            if (travelled1[m1[ind][i]] == 2)
            {
                travelled1[m1[ind][i]] = 1;
                dfs_visit(travelled1, m1[ind][i], ch, m1, time, ftimes1);
            }
            else if (travelled1[m1[ind][i]] == 1)
            {
                ch = false;
                travelled1[ind]=0;
                return;
            }
            if(!ch){
                break;
            }
        }
        time++;
        ftimes1[ind] = time;
        travelled1[ind] = 0;
    }
};
class maxHype : public GraphAlgorithm
{
public:
    void Query(vector<lwi> &v1, vector<vector<lwi>> &m1)
    {
        // func for computing max total hype score
        lwi len_v1 = v1.size(), t = 0;
        vector<lwi> travelled(len_v1, 2), ftimes(len_v1, 0);
        for (lwi i = 1; i < len_v1; i++)
        {
            if (travelled[i] == 2)
            {
                travelled[i] = 1;
                dfs_visit(travelled, i, m1, t, ftimes);
            }
        }
        vector<pair<lwi, lwi>> vert_ftime;
        for (lwi i = 1; i < len_v1; i++)
        {
            vert_ftime.push_back({i, ftimes[i]});
        }
        sort(vert_ftime.begin(), vert_ftime.end(), Toposort());
        vector<lwi> modified_vert_seq(len_v1, 0);
        for (lwi i = 1; i < len_v1; i++)
        {
            modified_vert_seq[i] = vert_ftime[i - 1].first;
        }
        vector<vector<lwi>> adj_list_gt(len_v1);
        for (lwi i = 1; i < len_v1; i++)
        {
            lwi adj_len = m1[i].size();
            for (lwi j = 0; j < adj_len; j++)
            {
                adj_list_gt[m1[i][j]].push_back(i);
            }
        }
        vector<lwi> SCC_ind(len_v1, 0);
        vector<lwi> combined_maxhype;
        lwi scc_ind_no = 0, scc_maxhypei = 0;
        vector<lwi> travelled2(len_v1, 2);
        for (lwi i = 1; i < len_v1; i++)
        {
            lwi ind = modified_vert_seq[i];
            if (travelled2[ind] == 2)
            {
                travelled2[ind] = 1;
                scc_maxhypei = 0;
                dfs_visit2(v1, travelled2, ind, adj_list_gt, scc_ind_no, SCC_ind, scc_maxhypei);
                scc_ind_no++;
                combined_maxhype.push_back(scc_maxhypei);
            }
        }
        vector<lwi> original_max_hype(combined_maxhype.begin(),combined_maxhype.end());
        vector<set<lwi>> Gscc_adj_list(scc_ind_no);
        for (lwi i = 1; i < len_v1; i++)
        {
            lwi adj_len = m1[i].size();
            for (lwi j = 0; j < adj_len; j++)
            {
                lwi v = m1[i][j];
                if (SCC_ind[i] != SCC_ind[v])
                {
                    Gscc_adj_list[SCC_ind[i]].insert(SCC_ind[v]);
                }
            }
        }
        vector<vector<lwi>> GsccT(scc_ind_no);
        for(lwi i=0;i<scc_ind_no;i++){
            lwi adj_len=Gscc_adj_list[i].size();
            for(auto& j:Gscc_adj_list[i]){
                GsccT[j].push_back(i);
            }
        }
        vector<lwi> indegree_scc(scc_ind_no);
        for(lwi i=0;i<scc_ind_no;i++){
            indegree_scc[i]=GsccT[i].size();
        }
        // lwi maxhype_allsccs = 0;
        // for (lwi i = 0; i < scc_ind_no; i++)
        // {
        //     lwi p = calculate_maxhype_i(Gscc_adj_list, i, combined_maxhype);
        //     maxhype_allsccs = max(maxhype_allsccs, p);
        // }
        // cout << maxhype_allsccs << endl;
        queue<lwi> sources;
        for(lwi i=0;i<scc_ind_no;i++){
            if(indegree_scc[i]==0){
                sources.push(i);
            }
        }
        while(!sources.empty()){
            lwi p=sources.front();
            sources.pop();
            lwi hypescore_parent=combined_maxhype[p];
            for(auto& j:Gscc_adj_list[p]){
                combined_maxhype[j]=max(combined_maxhype[j],combined_maxhype[p]+original_max_hype[j]);
                indegree_scc[j]--;
                if(indegree_scc[j]==0){
                    sources.push(j);
                }
            }
        }
        sort(combined_maxhype.begin(),combined_maxhype.end());
        cout<<combined_maxhype[scc_ind_no-1]<<endl;
    }
    void dfs_visit(vector<lwi> &travelled1, lwi ind, vector<vector<lwi>> &m1, lwi &time, vector<lwi> &ftimes1)
    {
        time++;
        travelled1[ind] = 1;
        lwi adj_len = m1[ind].size();
        for (lwi i = 0; i < adj_len; i++)
        {
            if (travelled1[m1[ind][i]] == 2)
            {
                travelled1[m1[ind][i]]=1;
                dfs_visit(travelled1, m1[ind][i], m1, time, ftimes1);
            }
        }
        time++;
        ftimes1[ind] = time;
        travelled1[ind] = 0;
    }
    void dfs_visit2(vector<lwi> &vec1, vector<lwi> &travelled, lwi ind, vector<vector<lwi>> &m1, lwi &sccindno1, vector<lwi> &SCC1, lwi &sccmaxhype1)
    {
        SCC1[ind] = sccindno1;
        sccmaxhype1 += vec1[ind];
        lwi adj_len = m1[ind].size();
        for (lwi i = 0; i < adj_len; i++)
        {
            if (travelled[m1[ind][i]] == 2)
            {
                travelled[m1[ind][i]]=1;
                SCC1[m1[ind][i]] = sccindno1;
                dfs_visit2(vec1, travelled, m1[ind][i], m1, sccindno1, SCC1, sccmaxhype1);
            }
        }
        travelled[ind] = 0;
    }
    lwi calculate_maxhype_i(vector<set<lwi>> &Gscc_adj_list1, lwi i1, vector<lwi> &combined_maxhype1)
    {
        lwi v_len = Gscc_adj_list1.size();
        vector<bool> travelled(v_len, 0);
        priority_queue<pair<lwi, lwi>, vector<pair<lwi, lwi>>, paircomparator> pq;
        lwi scc_maxhype = 0;
        pq.push({i1, combined_maxhype1[i1]});
        while (!pq.empty())
        {
            lwi ind = pq.top().first, hype = pq.top().second;
            travelled[ind] = 1;
            pq.pop();
            scc_maxhype = max(hype, scc_maxhype);
            for (auto &i : Gscc_adj_list1[ind])
            {
                if (travelled[i] == 0)
                {
                    lwi p = hype + combined_maxhype1[i];
                    pq.push({i, p});
                }
            }
        }
        return scc_maxhype;
    }
};
int main()
{
    lwi n, m;
    cin >> n >> m;
    vector<lwi> node_info(n + 1); // creating a vector of node class obj to pass into valid order class's query function
    for (lwi i = 0; i < n; i++)
    {
        lwi hypescore1;
        cin >> hypescore1;
        node_info[i + 1] = hypescore1;
    }
    vector<vector<lwi>> adj_list(n + 1); // creating an adj list to pass as a parameter for all classes Query func
    for (lwi i = 0; i < m; i++)
    {
        lwi u, v;
        cin >> u >> v;
        adj_list[u].push_back(v); // creating the nodes u and v for adj_list map
    }
    for (lwi i = 1; i < n + 1; i++)
    {
        sort(adj_list[i].begin(), adj_list[i].end(), greater<int>());
    }
    lwi q;
    cin >> q;
    for (lwi i = 0; i < q; i++)
    {
        lwi q_no;
        cin >> q_no;

        // based on the query no creating a particlar type of class and calling the query function

        if (q_no == 1)
        {
            isCycle g1;
            g1.Query(node_info, adj_list);
        }
        else if (q_no == 2)
        {
            indepComponent g2;
            g2.Query(node_info, adj_list);
        }
        else if (q_no == 3)
        {
            validOrder g3;
            g3.Query(node_info, adj_list);
        }
        else
        {
            maxHype g4;
            g4.Query(node_info, adj_list);
        }
    }
}