#include "../skeleton/solution.hpp"
#include <cassert>
#include <vector>
int main(){
    {
        std::vector<Employee> in{{2,10},{1,20},{2,30},{1,40}};
        auto r = sort_by_department(in);
        assert(r.size()==4);
        assert(r[0].dept_id==1 && r[0].emp_id==20);
        assert(r[1].dept_id==1 && r[1].emp_id==40);
        assert(r[2].dept_id==2 && r[2].emp_id==10);
        assert(r[3].dept_id==2 && r[3].emp_id==30);
    }
    {
        std::vector<Employee> in{};
        auto r = sort_by_department(in);
        assert(r.empty());
    }
    {
        std::vector<Employee> in{{5,1}};
        auto r = sort_by_department(in);
        assert(r.size()==1 && r[0].dept_id==5);
    }
    {
        std::vector<Employee> in{{1,1},{1,2},{1,3}};
        auto r = sort_by_department(in);
        assert(r[0].emp_id==1 && r[1].emp_id==2 && r[2].emp_id==3);
    }
    {
        std::vector<Employee> in{{3,100},{1,200},{3,300},{1,400},{2,500}};
        auto r = sort_by_department(in);
        assert(r[0].emp_id==200 && r[1].emp_id==400);
        assert(r[2].emp_id==500);
        assert(r[3].emp_id==100 && r[4].emp_id==300);
    }
    return 0;
}
