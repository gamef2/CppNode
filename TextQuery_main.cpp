#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<map>
#include<set>
#include<algorithm>
#include<iterator>
#include<sstream>
#include<fstream>
using namespace std;

class QueryResult;
class TextQuery
{
public:
    using line_no=vector<string>::size_type;
    TextQuery(fstream &);
    QueryResult query(const string&)const;
private:
    shared_ptr<vector<string>> file;
    map<string,shared_ptr<set<line_no>>> wm;
    static string cleanup_str(const string &word)
    {
        string ret;
        for(auto i:word)
            if(!ispunct(i))
                ret+=tolower(i);
        return ret;
    }
};
TextQuery::TextQuery(fstream &in):file(new vector<string>)
{
    string text;
    while(getline(in,text))
    {
        file->push_back(text);
        int n=file->size()-1;
        istringstream line(text);
        string word;
        while(line>>word)
        {
            shared_ptr<set<line_no>> &lines=wm[cleanup_str(word)];
            if(!lines)
                lines.reset(new set<line_no>);
            lines->insert(n);
        }
    }
}
class QueryResult
{
    using line_no=vector<string>::size_type;
    using line_it=set<line_no>::const_iterator;
    friend ostream& operator<<(ostream &os,const QueryResult&);
public:
    QueryResult(string s,
                shared_ptr<set<line_no>> p,
                shared_ptr<vector<string>> f)
        :sought(s),lines(p),file(f) {}
    line_it begin()const
    {
        return lines->begin();
    }
    line_it end()const
    {
        return lines->end();
    }
    shared_ptr<vector<string>> get_file()
    {
        return file;
    }
private:
    string sought;
    shared_ptr<set<line_no>> lines;
    shared_ptr<vector<string>> file;
};
QueryResult TextQuery::query(const string &word)const
{
    shared_ptr<set<line_no>> nodata(new set<line_no>);
    map<string,shared_ptr<set<line_no>>>::const_iterator it=wm.find(cleanup_str(word));
    if(it!=wm.end())
        return QueryResult(word,it->second,file);
    else
        return QueryResult(word,nodata,file);
}
ostream& operator<<(ostream& os,const QueryResult &rhs)
{
    os<<rhs.sought<<" occur "<<(rhs.lines->size())<<" "
      <<(rhs.lines->size()>=1?"times":"time")<<endl;
    for(auto n:*rhs.lines)
        os<<"\t( " <<n+1<<" ) "
          <<*(rhs.file->begin()+n)<<endl;
    return os;
}
void RunQueries(fstream &infile)
{
    TextQuery tq(infile);
    while(true)
    {
        string s;
        cout<<"ÊäÈë²éÕÒÄÚÈÝ:"<<endl;
        if(!(cin>>s)||s=="q")
            break;
        cout<<tq.query(s)<<endl;
    }
}

class Query;
class Query_base
{
    friend Query;
protected:
    using line_no=TextQuery::line_no;
    virtual ~Query_base() {}
private:
    virtual QueryResult eval(const TextQuery&)const=0;
    virtual string rep()const=0;
};
class Query
{
    friend Query operator~(const Query&);
    friend Query operator&(const Query&,const Query&);
    friend Query operator|(const Query&,const Query&);
public:
    Query(const string&);
    Query(shared_ptr<Query_base> query)
        :q(query) {}
    QueryResult eval(const TextQuery &text)const
    {
        return q->eval(text);
    }

    string rep()const
    {
        return q->rep();
    }
    shared_ptr<Query_base> q;
};
ostream& operator<<(ostream& os,const Query &rhs)
{
    return os<<rhs.rep();
}
class WordQuery:public Query_base
{
    friend Query;
    WordQuery(const string &word)
        :query_word(word) {}
    QueryResult eval(const TextQuery& text)const
    {
        return text.query(query_word);
    }
    string rep()const
    {
        return query_word;
    }
    string query_word;
};
inline Query::Query(const string &s):q(new WordQuery(s)) {}

class NotQuery:public Query_base
{
    friend Query operator~(const Query&);
    NotQuery(const Query &q)
        :query(q) {}
    QueryResult eval(const TextQuery&)const;
    string rep()const
    {
        return "~("+query.rep()+")";
    }
    Query query;
};
inline Query operator~(const Query &operand)
{
    return shared_ptr<Query_base>(new NotQuery(operand));
}
QueryResult NotQuery::eval(const TextQuery &text)const
{
    QueryResult result=query.eval(text);
    shared_ptr<set<line_no>> ret_lines=make_shared<set<line_no>>();
    set<line_no>::iterator beg=result.begin(),end=result.end();
    size_t sz=result.get_file()->size();
    for(size_t i=0; i<sz; ++i)
    {
        if(beg==end||*beg!=i)
            ret_lines->insert(i);
        else if(beg!=end)
            ++beg;
    }
    return QueryResult(rep(),ret_lines,result.get_file());
}

class BinaryQuery:public Query_base
{
protected:
    BinaryQuery(const Query &l,const Query &r,string s)
        :lhs(l),rhs(r),opSym(s) {}
    string rep()const
    {
        return "("+lhs.rep()+" "
               +opSym+" "
               +rhs.rep()+")";
    }
    Query lhs,rhs;
    string opSym;
};

class AndQuery:public BinaryQuery
{
    friend Query operator&(const Query &lhs,const Query &rhs);
    AndQuery(const Query &l,const Query &r)
        :BinaryQuery(l,r,"&") {}
    QueryResult eval(const TextQuery&)const;
};
inline Query operator&(const Query &lhs,const Query &rhs)
{
    return shared_ptr<Query_base>(new AndQuery(lhs,rhs));
}
QueryResult AndQuery::eval(const TextQuery &text)const
{
    QueryResult left=lhs.eval(text),right=rhs.eval(text);
    shared_ptr<set<line_no>> ret_line=make_shared<set<line_no>>();
    set_intersection(left.begin(),left.end(),
                     right.begin(),right.end(),
                     inserter(*ret_line,ret_line->begin()));
    return QueryResult(rep(),ret_line,left.get_file());
}
class OrQuery:public BinaryQuery
{
    friend Query operator|(const Query &lhs,const Query &rhs);
    OrQuery(const Query &l,const Query &r)
        :BinaryQuery(l,r,"|") {}
    QueryResult eval(const TextQuery&)const;
};
inline Query operator|(const Query &lhs,const Query &rhs)
{
    return shared_ptr<Query_base>(new OrQuery(lhs,rhs));
}
QueryResult  OrQuery::eval(const TextQuery &text)const
{
    QueryResult left=lhs.eval(text),right=rhs.eval(text);
    shared_ptr<set<line_no>> ret_line=
                              make_shared<set<line_no>>(left.begin(),left.end());
    ret_line->insert(right.begin(),right.end());
    return QueryResult(rep(),ret_line,left.get_file());
}
void initFile()
{
    fstream out("1.txt",ios::out|ios::binary);
    out<<"Alice Emma has long flowing red hair.\n"
       "Her Daddy says when the wind blows\n"
       "through her hair, it looks almost alive,\n"
       "like a fiery bird in flight.\n"
       "A beautiful fiery bird, he tells her,\n"
       "magical but untamed.\n"
       "\042Daddy, shush, there is no such thing,\042\n"
       "she tells him, at the same time wanting\n"
       "him to tell her more.\n"
       "Shyly, she asks, \042I mean, Daddy, is there?\042\n";
    out.close();
}
int main(int argc, char *argv[])
{
    initFile();
    fstream in("1.txt");
    if (!in)
        exit(1);
    TextQuery file(in);
    Query q = Query("hair") &Query("Alice");
    auto results = q.eval(file);
    cout << results << endl;

    q = Query("hair") | Query("Alice");
    results = q.eval(file);
    cout << results << endl;

    q = ~Query("hair");
    results = q.eval(file);
    cout << results << endl;
    q = (Query("hair")&Query("bird")) | Query("wind");
    results = q.eval(file);
    cout << results << endl;
    in.close();/*
    initFile();
    fstream in("1.txt");
    if (!in)
        exit(1);
    RunQueries(in);
    in.close();
*/
    return 0;
}
